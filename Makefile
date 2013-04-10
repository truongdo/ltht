CLIENT = client
SERVER = server
all:
	(cd $(CLIENT) && $(MAKE) all)
	(cd $(SERVER) && $(MAKE) all)
clean:
	rm client/client
	rm server/server
