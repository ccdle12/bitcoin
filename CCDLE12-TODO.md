# TODO

- [ ] Analyze `httpserver.cpp` - specifically
  - How is the request made?
  - Where is the actual request code?
  - Who is it making the request to and where is the request being received?
  - Trail of calls to follow:
      - `obtain_evhttp_request(http_request_done, (void*)&response)` in `bitcoin-cli.cpp` on line `321`.
      - `obtain_evhttp_request()` in `events.h` on line `47`.
      - `http_request_done` in `bitcoin-cli.cpp` on line `179`.  

  
