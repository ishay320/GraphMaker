# Graph maker

Creates graphs of the cpp/c project:

- class
- file connections
- functions

**this is a project in progress - its not done yet!**

## Example of include graph output
```mermaid
graph TD

    utils.h(utils.h)
    utils.h --> |system| filesystem
    utils.h --> |system| string
    utils.h --> |system| vector

    graphMaker.cpp(graphMaker.cpp)
    graphMaker.cpp --> |local| graphMaker.h
    graphMaker.cpp --> |local| utils.h

    graphMaker.h(graphMaker.h)
    graphMaker.h --> |system| filesystem
    graphMaker.h --> |system| fstream
    graphMaker.h --> |system| iostream
    graphMaker.h --> |system| string
    graphMaker.h --> |system| vector

    utils.cpp(utils.cpp)
    utils.cpp --> |local| utils.h

    main.cpp(main.cpp)
    main.cpp --> |system| filesystem
    main.cpp --> |system| fstream
    main.cpp --> |system| iostream
    main.cpp --> |system| string
    main.cpp --> |system| vector
    main.cpp --> |local| graphMaker.h
    main.cpp --> |local| utils.h
```

## How to run

1. install `cmake`
1. `mkdir build`
1. `cd build`
1. `cmake ..`
1. `make`
1. `./main <path> [exclude list] `

## How to convert mermaid to graph

1. install npm `sudo apt install npm`
1. `npm install @mermaid-js/mermaid-cli`
1. `./node_modules/.bin/mmdc -h`
> example: `./node_modules/.bin/mmdc -i ./includes.txt -o includes.pdf -f` 
### If have an error

```bash
$ sudo apt-get update
$ sudo apt-get install -y libgbm-dev
# sometimes needs more:
$ sudo apt-get install libatk1.0-0 libatk-bridge2.0-0 libcups2 libxkbcommon-x11-0 libxcomposite1 libxdamage1 libxfixes3 libxrandr2 libgbm1 libpango-1.0-0 libcairo2
```
