# Async
## Multithreaded asynchronous command processing on the server
### Using
```
bulk_server <port> <bulk_size> [mode]
```
- **port** - tcp port number for incoming connections.
- **bulk_size** - command block size.
- **mode** - operation mode: *line* or *symbolic* (optional, *line* by default).