# game_of_life
Conway's game of life

# build instructions
required packages:
- gcc
- make
- git

These will be pre-installed on most Debian based systems, but if not, try:
```
sudo apt install gcc make git
```

Then clone this repository:
```
git clone https://github.com/amurph24/game_of_life.git
```

navigate into the directory and build the executable:
```
cd game_of_life
make life
```

You can then execute it from the 'build' dir, or do `make run`.
