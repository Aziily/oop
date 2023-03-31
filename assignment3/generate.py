from random import randint, choice
from enum import Enum
 
 
class ITEM_TYPE(Enum):
    EMPTY = 0,
    BLOCK = 1,
 
class DIRECTION(Enum):
    LEFT = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
 
 
class Map():
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.start = (0, 0)
 
        # 初始化均为墙
        self.map = [[1 for x in range(self.width)] for y in range(self.height)]
 
    def resetMap(self, value):
        for y in range(self.height):
            for x in range(self.width):
                self.setMap(x, y, value)
 
    def setMap(self, x, y, value):
        if value == ITEM_TYPE.EMPTY:
            self.map[y][x] = 0
        elif value == ITEM_TYPE.BLOCK:
            self.map[y][x] = 1
 
    def isVisited(self, x, y):
        return self.map[y][x] == 0
 
    def showMap(self):
        for row in self.map:
            for item in row:
                if item == 0:
                    print('  ', end='')
                elif item == 1:
                    print('@ ', end='')
                elif item == 2:
                    print('! ', end='')
                elif item == 3:
                    print('? ', end='')
                elif item == 4:
                    print('$ ', end='')
            print('')
            
    def writeFile(self, filename):
        with open(filename, 'w') as f:
            f.write(str(self.width) + ' ' + str(self.height) + '\n')
            f.write(str(self.start[1] + 1) + ' ' + str(self.start[0] + 1) + '\n')
            for row in range(self.height):
                for col in range(self.width):
                    item = self.map[row][col]
                    line = ""
                    if item == 0 or item == 1 or item == 4:
                        line += '0'
                    elif item == 2:
                        line += '1'
                    elif item == 3:
                        line += '2'
                    if (row != 0 and self.map[row - 1][col] != 1) :
                        line += ' 1'
                    else:
                        line += ' 0'
                    if (col != self.width - 1 and self.map[row][col + 1] != 1):
                        line += ' 1'
                    else :
                        line += ' 0'
                    if (row != self.height - 1 and self.map[row + 1][col] != 1):
                        line += ' 1'
                    else:
                        line += ' 0'
                    if (col != 0 and self.map[row][col - 1] != 1):
                        line += ' 1'
                    else:
                        line += ' 0'
                    line += '\n'
                    f.write(line)
    
    def addSomething(self):
        exit = False
        for i in range(1, self.width - 1):
            if exit:
                break;
            if (randint(0, 1) == 1 and self.map[1][i] == 0):
                self.map[0][i] = 0
                exit = True
                break;
        for i in range(1, self.width - 1):
            if exit:
                break;
            if (randint(0, 1) == 1 and self.map[self.height - 2][i] == 0):
                self.map[self.height - 1][i] = 0
                exit = True
                break;
        for j in range(1, self.height - 1):
            if exit:
                break;
            if (randint(0, 1) == 1 and self.map[j][1] == 0):
                self.map[j][0] = 0
                exit = True
                break;
        for j in range(1, self.height - 1):
            if exit:
                break;
            if (randint(0, 1) == 1 and self.map[j][self.width - 2] == 0):
                self.map[j][self.width - 1] = 0
                exit = True
                break;
        blank = []
        for row in range(1, self.height - 1):
            for col in range(1, self.width - 1):
                if self.map[row][col] == 0:
                    blank.append((row, col))
        
        rd = randint(0, len(blank) - 1)
        self.map[blank[rd][0]][blank[rd][1]] = 2
        blank.remove(blank[rd])
        
        rd = randint(0, len(blank) - 1)
        self.map[blank[rd][0]][blank[rd][1]] = 3
        blank.remove(blank[rd])
        
        rd = randint(0, len(blank) - 1)
        self.map[blank[rd][0]][blank[rd][1]] = 4
        self.start = blank[rd]
        blank.remove(blank[rd])
 
def checkPostion(map, x, y, widthLimited, heightLimited, waitinglist):
    directions = []
    if x > 0:
        if not map.isVisited(2 * (x - 1) + 1, 2 * y + 1):
            directions.append(DIRECTION.LEFT)
    if y > 0:
        if not map.isVisited(2 * x + 1, 2 * (y - 1) + 1):
            directions.append(DIRECTION.UP)
    if x < widthLimited - 1:
        if not map.isVisited(2 * (x + 1) + 1, 2 * y + 1):
            directions.append(DIRECTION.RIGHT)
    if y < heightLimited - 1:
        if not map.isVisited(2 * x + 1, 2 * (y + 1) + 1):
            directions.append(DIRECTION.DOWN)
 
    if len(directions):
        # 随机选择方向
        direction = choice(directions)
 
        if direction == DIRECTION.LEFT:
            map.setMap(2 * (x - 1) + 1, 2 * y + 1, ITEM_TYPE.EMPTY)
            map.setMap(2 * x, 2 * y + 1, ITEM_TYPE.EMPTY)
            waitinglist.append((x - 1, y))
        elif direction == DIRECTION.UP:
            map.setMap(2 * x + 1, 2 * (y - 1) + 1, ITEM_TYPE.EMPTY)
            map.setMap(2 * x + 1, 2 * y, ITEM_TYPE.EMPTY)
            waitinglist.append((x, y - 1))
        elif direction == DIRECTION.RIGHT:
            map.setMap(2 * (x + 1) + 1, 2 * y + 1, ITEM_TYPE.EMPTY)
            map.setMap(2 * x + 2, 2 * y + 1, ITEM_TYPE.EMPTY)
            waitinglist.append((x + 1, y))
        elif direction == DIRECTION.DOWN:
            map.setMap(2 * x + 1, 2 * (y + 1) + 1, ITEM_TYPE.EMPTY)
            map.setMap(2 * x + 1, 2 * y + 2, ITEM_TYPE.EMPTY)
            waitinglist.append((x, y + 1))
        return True
    else:
        return False
 
 
def recursive(map, widthLimited, heightLimited):
    startX, startY = (randint(0, widthLimited - 1), randint(0, heightLimited - 1))
    map.setMap(2 * startX + 1, 2 * startY + 1, ITEM_TYPE.EMPTY)
 
    waitinglist = []
    waitinglist.append((startX, startY))
    while len(waitinglist):
        if not checkPostion(map, waitinglist[-1][0], waitinglist[-1][1], widthLimited, heightLimited, waitinglist):
            waitinglist.remove(waitinglist[-1])
 
# 开始构造迷宫
def startCreateMaze(map):
    recursive(map, map.width // 2, map.height // 2)
 
def run():
    WIDTH = 27
    HEIGHT = 17
    map = Map(WIDTH, HEIGHT)
    startCreateMaze(map)
    map.addSomething()
    map.showMap()
    map.writeFile("./data/data.txt")

if __name__ == "__main__":
    run()