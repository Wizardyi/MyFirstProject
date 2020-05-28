#!/usr/bin/env perl

use warnings;
use strict;

use Data::Dumper;
use JSON;

sub load_config {
    my $path = shift;

    open my $fh, "<", $path or die "load config file [$path] fail, $!\n";

    my $json = JSON->new->allow_nonref;
    my $config = $json->decode(join("", <$fh>));

    close $fh;

    return $config;
}

sub load_create_table_sqls {
    my $sql_files = shift;
    
    my $sql_content = "";

    foreach my $sql_file (@$sql_files) {
        open FILE, "<", $sql_file;
        $sql_content .= join('', <FILE>);
        close FILE;
    }

    my %sqls = ();

    my $re_create_table_sql = qr/CREATE TABLE IF NOT EXISTS `([A-Za-z0-9_]+)`[ \t\n()=a-zA-Z0-9_`',]+;/;

    while ($sql_content =~ /$re_create_table_sql/g) {
        $sqls{$1} = $&;
    }

    return \%sqls;
}

my $split_config = load_config(<'./migrate_tables_config.json'>);

# print Dumper($split_config);

my @sql_files = ('./ink_sanguo_mysql.sql', './ink_sanguo_pay_mysql.sql');

my $sqls = &load_create_table_sqls(\@sql_files);

# print Dumper($sqls);

my $mysql_info = {
    host => '192.168.1.235',
    user => 'inksg',
    password => 'isg@mysql'
};

sub mysql_cmd {
    my $db = shift;

    return "mysql -h$mysql_info->{host} -u$mysql_info->{user} -p$mysql_info->{password} $db";
}

sub sql_cmd {
    my $db = shift;
    my $sql = shift;

    return sprintf("cat << EOF | %s\n%s\nEOF", mysql_cmd($db), $sql);
}

sub append_num_suffix {
    my $str = shift || "";
    my $idx = shift || 0;
    my $max = shift || 9;

    my $n = 1;
    
    if ($max < 10) {
        $n = 1;
    } elsif ($max < 100) {
        $n = 2;
    } elsif ($max < 1000) {
        $n = 3;
    } elsif ($max < 10000) {
        $n = 4;
    }

    if ($n > 1) {
        return sprintf("%s_%0${n}d", $str, $idx);
    } else {
        return sprintf("%s_%d", $str, $idx);
    }
}

open FILE_CREATE_ALL, ">", "create_all_migrate_tables.sh";

foreach my $conf (values %$split_config) {
    next if $conf->{ignore} or not $conf->{db};

    foreach my $tbl_name (@{$conf->{tables}}) {
        my $sql = $sqls->{$tbl_name};

        if ($sql) {
            print "> $conf->{db}.$tbl_name\n";

            my $sql_file = "create_$tbl_name.sql";
            my $bash_file = "create_$tbl_name.sh";

            open FILE, ">", $sql_file;
            print FILE $sql, "\n\n";
            close FILE;

            open FILE, ">", $bash_file;
            if ($conf->{num_db} == 1 and $conf->{num_tbl} == 1) {
                print FILE "./create_table.sh $conf->{db} ./$sql_file\n";
            } else {
                print FILE "./create_tables.sh $conf->{db} ./$sql_file $conf->{num_db} $conf->{num_tbl}\n";
            }
            close FILE;

            # if ($conf->{num_db} == 1 and $conf->{num_tbl} == 1) {
            #     open FILE, ">", $sql_file;
            #     print FILE $sql, "\n\n";
            #     close FILE;
            #
            #     open FILE, ">", $bash_file;
            #     print FILE "./create_table.sh $conf->{db} ./$sql_file\n";
            #     close FILE;
            # } elsif ($conf->{num_db} >= 1 and $conf->{num_tbl} >= 1) {
            #     open FILE, ">", $sql_file;
            #
            #     foreach my $idx_db (0 .. $conf->{num_db}-1) {
            #         foreach my $idx_tbl (0 .. $conf->{num_tbl}-1) {
            #             my $new_tbl_name = append_num_suffix($tbl_name, $idx_tbl, $conf->{num_tbl}-1);
            #
            #             my $new_sql = $sql;
            #             $new_sql =~ s/`$tbl_name`/`$new_tbl_name`/;
            #
            #             print FILE $new_sql, "\n\n";
            #         }
            #     }
            #
            #     close FILE;
            #
            #     open FILE, ">", $bash_file;
            #     print FILE "./create_tables.sh $conf->{db} ./$sql_file $conf->{num_db} $conf->{num_tbl}\n";
            #     close FILE;
            # } else {
            #     print "invalid db number or table number paramter for generating table $tbl_name\n";
            # }

            print FILE_CREATE_ALL "./$bash_file\n";
        } else {
            print "can't find sql for $tbl_name\n";
        }
    }
}

close FILE_CREATE_ALL;
