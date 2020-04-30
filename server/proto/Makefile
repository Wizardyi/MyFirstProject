PROTODIR = ./

PROTO_CACHE_MAKEFILES_DIR = $(PROTODIR)/cache/define
PROTO_DB_MAKEFILES_DIR = $(PROTODIR)/db/define
PROTO_LOGIN_MAKEFILES_DIR = $(PROTODIR)/login/define
PROTO_ONLINE_MAKEFILES_DIR = $(PROTODIR)/online/define
PROTO_SHARE_MAKEFILES_DIR = $(PROTODIR)/share/define
PROTO_SWITCH_MAKEFILES_DIR = $(PROTODIR)/switch/define
PROTO_GATE_MAKEFILES_DIR = $(PROTODIR)/gate/define
PROTO_POSITION_MAKEFILES_DIR = $(PROTODIR)/position/define

all: share_proto cache_proto db_proto login_proto online_proto switch_proto gate_proto position_proto 


share_proto:
	+make -C $(PROTO_SHARE_MAKEFILES_DIR)

cache_proto: share_proto
	+make -C $(PROTO_CACHE_MAKEFILES_DIR)

db_proto: share_proto
	+make -C $(PROTO_DB_MAKEFILES_DIR)


login_proto: share_proto
	+make -C $(PROTO_LOGIN_MAKEFILES_DIR)

online_proto: share_proto
	+make -C $(PROTO_ONLINE_MAKEFILES_DIR)

switch_proto: share_proto
	+make -C $(PROTO_SWITCH_MAKEFILES_DIR)


gate_proto: share_proto
	+make -C $(PROTO_GATE_MAKEFILES_DIR)

position_proto: share_proto
	+make -C $(PROTO_POSITION_MAKEFILES_DIR)

clean:
	+make -C $(PROTO_CACHE_MAKEFILES_DIR) clean
	+make -C $(PROTO_DB_MAKEFILES_DIR) clean
	+make -C $(PROTO_LOGIN_MAKEFILES_DIR) clean
	+make -C $(PROTO_ONLINE_MAKEFILES_DIR) clean
	+make -C $(PROTO_SHARE_MAKEFILES_DIR) clean
	+make -C $(PROTO_SWITCH_MAKEFILES_DIR) clean
	+make -C $(PROTO_GATE_MAKEFILES_DIR) clean
	+make -C $(PROTO_POSITION_MAKEFILES_DIR) clean
