# yykk's magic tower game
my first game

## Introduction
In this game, you'll act as a hero and is assigned to kill the evil Beelzebub.
Be careful, since he has many strong monsters: slime, skeleton, bat, and
scary apostle! To beat them, you should explore the map consisting of many
floors, and collect powerful weapons and armors. If you lose health, whether
caused by monsters or lava, remember to use blood bottle to heal yourself.

Now, the brave hero, install the game and defeat the Beelzebub!

## Operations
Here is the way you can operate the hero:

| Key | Operation                   |
|-----|-----------------------------|
|  W  | move up                     |
|  A  | move left                   |
|  S  | move down                   |
|  D  | move right                  |
|  Q  | use the small bottle        |
|  E  | use the big bottle          |
|  R  | restart the game            |
|  X  | show monsters' informations |
|  Z  | exit the game               |


## Elements
### hero

| name      | description   | hp   | attack   | defence   |
| --------- | ------------- | ---- | -------- | --------- |
| Hero      | brave you     | 50   | 20       | 5         |

### monsters

| name      | description   | hp   | attack   | defence   | score   | skill            |
| --------- | ------------- | ---- | -------- | --------- | ------- | -------          |
| Slime     | weak          | 10   | 5        | 5         | 5       | none             |
| Skeleton  | annoying      | 16   | 8        | 8         | 8       | none             |
| Bat       | frightening   | 25   | 15       | 0         | 10      | blood-sucking    |
| Apostle   | scary         | 50   | 30       | 15        | 25      | mental pollution |
| Beelzebub | evil          | 100  | 25       | 15        | 100     | none             |

### objects

| name               | description                                |
|--------------------|--------------------------------------------|
| wall               | you can't walk across or destroy them      |
| space              | feel free to walk on                       |
| lava               | don't walk on it! you will lose 1 hp       |
| door               | you can't access them unless you use a key |
| key                | collect to open the door                   |
| up block           | go to next floor                           |
| down block         | go to previous floor                       |
| small blood bottle | heal 10 hp                                 |
| big blood bottle   | heal 25 hp                                 |
| sword              | add 20 attack                              |
| shield             | add 10 defence                             |
| life gem           | add 50 hp limit                            |


## TODO
- [ ] refactor with classes
- [ ] GUI
    - [ ] pop-up to choose whether fight with monsters and whether open doors
- [ ] better maps
- [ ] custom keys
- [ ] more monsters and more objects
