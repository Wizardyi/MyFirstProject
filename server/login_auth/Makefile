CC = g++
WORKDIR = ./
SRCDIR = $(WORKDIR)
LIBDIR = $(WORKDIR)
OBJDIR = $(WORKDIR)/../../obj
DEPDIR = $(WORKDIR)/../../obj
INCLUDEDIR = $(WORKDIR)
BINDIR = $(WORKDIR)
PROTODIR = $(WORKDIR)/../../../proto
SHAREDIR = $(WORKDIR)/../../../share
PROTOBUF_CFLAGS = $(shell pkg-config --cflags protobuf glib-2.0)
PROTOBUF_LFLAGS = $(shell pkg-config --libs protobuf)


CFLAGS = -Wall -Werror -fPIC -ggdb -std=c++11  \
    -Iinclude -I/usr/local/lib/glib-2.0/include/ -I/usr/local/include/glib-2.0 \
    -I/usr/lib/glib-2.0/include/ -I/usr/include/glib-2.0 \
	-I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ \
	-I/usr/include/ \
    -I$(WORKDIR)/../../../  $(PROTOBUF_CFLAGS) -DOL_DEBUG -I/usr/include/libxml2 \
    -DOL_DEBUG -DUSE_TLOG -I$(PROTODIR) -I$(SHAREDIR) -I../

#LFLAGS = -ltaomee -ltaomee++ -lcrypto -ljsoncpp

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(subst $(SRCDIR),$(OBJDIR),$(SRCS)))
DEPS := $(patsubst %.cpp,%.d,$(subst $(SRCDIR),$(DEPDIR),$(SRCS)))
TARGET = liblogin_auth.a

all: $(TARGET)

$(TARGET): $(OBJS)
	ar r $(TARGET) $(OBJS)

#由于obj生成在$(OBJDIR)中，在依赖关系中加入目录
$(DEPDIR)/%.d: $(SRCDIR)/%.cpp
	@echo "generate $@"
	@printf "$(OBJDIR)/" > $@.tmp
	@$(CC) -MM $< $(CFLAGS) >> $@.tmp 2> /dev/null
	@mv $@.tmp $@
    
sinclude $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm $(OBJS) $(DEPS)
