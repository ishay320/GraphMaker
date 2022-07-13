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
    utils.h --> filesystem
    utils.h --> string
    utils.h --> vector
	linkStyle 0,1,2 stroke-width:2px,fill:none,stroke:blue;
	style utils.h stroke-width:2px,fill:bisque,stroke:blue;

    graphMaker.cpp(graphMaker.cpp)
    graphMaker.cpp --> graphMaker.h
    graphMaker.cpp --> utils.h
	linkStyle 3,4 stroke-width:2px,fill:none,stroke:black;
	style graphMaker.cpp stroke-width:2px,fill:lightgreen,stroke:black;

    graphMaker.h(graphMaker.h)
    graphMaker.h --> filesystem
    graphMaker.h --> fstream
    graphMaker.h --> iostream
    graphMaker.h --> string
    graphMaker.h --> vector
	linkStyle 5,6,7,8,9 stroke-width:2px,fill:none,stroke:silver;
	style graphMaker.h stroke-width:2px,fill:bisque,stroke:silver;

    utils.cpp(utils.cpp)
    utils.cpp --> utils.h
    utils.cpp --> iostream
    utils.cpp --> string.h
	linkStyle 10,11,12 stroke-width:2px,fill:none,stroke:red;
	style utils.cpp stroke-width:2px,fill:lightgreen,stroke:red;

    main.cpp(main.cpp)
    main.cpp --> filesystem
    main.cpp --> fstream
    main.cpp --> iostream
    main.cpp --> string
    main.cpp --> vector
    main.cpp --> graphMaker.h
    main.cpp --> utils.h
	linkStyle 13,14,15,16,17,18,19 stroke-width:2px,fill:none,stroke:purple;
	style main.cpp stroke-width:2px,fill:lightgreen,stroke:purple;
```

## How to run

1. install `cmake`
1. `mkdir build`
1. `cd build`
1. `cmake ..`
1. `make`
1. `./graph-maker <path> [exclude list] `

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
