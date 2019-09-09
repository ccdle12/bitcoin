# TODO 
- [] Write a functional test
  - [X] How to run a single functional test
  - [X] How does it call the C++ code?
  - [] Test Scenario:
    - 3 Nodes
    - Mine to node1 (101 blocks)
    - There should be a UTXO of 1 for node1
    - Call wallet for node1 and it should be 50
    - Use the utxo and send it to node2 
    - Check that node2 ha received it
  - [] What is listunspent?
    - RPC
    - C++
  - [] How can I view the debug outputs?
 
- [X] Analyze `httpserver.cpp` - specifically
  - How is the request made?
  - Where is the actual request code?
  - Who is it making the request to and where is the request being received?
  - Trail of calls to follow:
      - `obtain_evhttp_request(http_request_done, (void*)&response)` in `bitcoin-cli.cpp` on line `321`.
      - `obtain_evhttp_request()` in `events.h` on line `47`.
      - `http_request_done` in `bitcoin-cli.cpp` on line `179`.  

  
