# Places server parameters

PLACES_TARGETS_CLNT.c = places_clnt.c places_client.c places_xdr.c 
PLACES_TARGETS_SVC.c = places_svc.c places_server.c places_xdr.c 

PLACES_OBJECTS_CLNT = $(PLACES_TARGETS_CLNT.c:%.c=%.o)
PLACES_OBJECTS_SVC = $(PLACES_TARGETS_SVC.c:%.c=%.o)


# Airports server parameters

AIRPORTS_TARGETS_CLNT.c = airports_clnt.c airports_client.c airports_xdr.c 
AIRPORTS_TARGETS_SVC.c = airports_svc.c airports_server.c airports_xdr.c 

AIRPORTS_OBJECTS_CLNT = $(AIRPORTS_TARGETS_CLNT.c:%.c=%.o)
AIRPORTS_OBJECTS_SVC = $(AIRPORTS_TARGETS_SVC.c:%.c=%.o)

# Trie parameters

CFLAGS += -I ./trie
TRIE_TARGETS = ./trie/trie.c
TRIE_OBJECTS = $(TRIE_TARGETS:%.c=%.o)


# K-D tree parameters

CFLAGS += -lm -I ./kdtree
KD_TARGETS = ./kdtree/kdtree.c
KD_OBJECTS = $(KD_TARGETS:%.c=%.o)


# Program parameters

CLIENT = client
PLACES = places
AIRPORTS = airports

CLIENT_OBJECTS = $(PLACES_OBJECTS_CLNT)
PLACES_OBJECTS = $(PLACES_OBJECTS_SVC) $(AIRPORTS_OBJECTS_CLNT) $(TRIE_OBJECTS)
AIRPORTS_OBJECTS = $(AIRPORTS_OBJECTS_SVC) $(KD_OBJECTS)


# Compiler flags

CFLAGS += -g -I /usr/include/tirpc
LDLIBS += -ltirpc
# LDLIBS += -lnsl
RPCGENFLAGS = 


# Targets

all : $(CLIENT) $(PLACES) $(AIRPORTS)

$(TRIE_OBJECTS) : $(TRIE_TARGETS) $(TRIE_TARGETS:%.c=%.h)
$(KD_OBJECTS) : $(KD_TARGETS) $(KD_TARGETS:%.c=%.h)

$(PLACES_OBJECTS_CLNT) : $(PLACES_TARGETS_CLNT.c) 
$(PLACES_OBJECTS_SVC) : $(PLACES_TARGETS_SVC.c)

$(AIRPORTS_OBJECTS_CLNT) : $(AIRPORTS_TARGETS_CLNT.c) 
$(AIRPORTS_OBJECTS_SVC) : $(AIRPORTS_TARGETS_SVC.c)

$(CLIENT) : $(CLIENT_OBJECTS) 
	$(LINK.c) -o $(CLIENT) $(CLIENT_OBJECTS) $(LDLIBS) 

$(PLACES) : $(PLACES_OBJECTS)
	$(LINK.c) -o $(PLACES) $(PLACES_OBJECTS) $(LDLIBS) 

$(AIRPORTS) : $(AIRPORTS_OBJECTS)
	$(LINK.c) -o $(AIRPORTS) $(AIRPORTS_OBJECTS) $(LDLIBS) -lm

clean:
	$(RM) core $(CLIENT_OBJECTS) $(PLACES_OBJECTS) $(AIRPORTS_OBJECTS) $(TRIE_OBJECTS) $(KD_OBJECTS) $(CLIENT) $(PLACES) $(AIRPORTS)
