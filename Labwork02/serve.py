import sys
from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.server import SimpleXMLRPCRequestHandler
import os
import time

# Restrict to a particular path.
class RequestHandler(SimpleXMLRPCRequestHandler):
    rpc_paths = ('/RPC2',)

# Create server
with SimpleXMLRPCServer(('localhost', 3000),
                        requestHandler=RequestHandler) as server:
    server.register_introspection_functions()

    # Register a function under a different name
    def file_transfer_function(datas,filename,dt):
        handle_file=open(filename.split('/')[-1],'wb')
        handle_file.write(datas.data)
        handle_file.close()
        return True
    print('Listerning on port 3000..........')
        
    server.register_function(file_transfer_function, 'file_transfer')
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nKeyboard interrupt received, exiting.")
        sys.exit(0)