#ifndef CASTLE_CPP
#define CASTLE_CPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Castle
{
private:
    struct CastleRoom
    {
        int kind;   // 0: empty, 1: princess, 2: monster, 3: exit
        bool exit_N, exit_E, exit_S, exit_W;    // 0: no exit, 1: exit
        CastleRoom() {}
        CastleRoom(int kind, bool exit_N, bool exit_E, bool exit_S, bool exit_W) \
            : kind(kind), exit_N(exit_N), exit_E(exit_E), exit_S(exit_S), exit_W(exit_W) {}
    };
    struct Player
    {
        int x, y;   // position
        bool meet_princess; // 0: not meet, 1: meet
        Player() {}
        Player(int x, int y, bool meet_princess=false) \
            : x(x), y(y), meet_princess(meet_princess) {}
    };
    
private:
    vector<vector<CastleRoom>> rooms;   // 1-indexed
    int width, height;  // width: x, height: y
    int start_x, start_y;   // start position
    Player player;  // player
    int state;  // 0: empty, 1: princess, 2: monster, 3: exit, 4: exit without princess

public:
    /// @brief Constructor
    /// @param file_path: path of data file
    Castle(string file_path);
    // ~Castle();

    /// @brief Move player to a new room
    /// @param direction: N, E, S, W
    void move(char direction);

    /// @brief Get current state
    /// @return state
    int get_state() { return state; }

    /// @brief Print information of the castle
    void print_info();

    /// @brief Print prompt of current room
    void print_room_prompt();

    /// @brief Print current state
    void print_state();
};

Castle::Castle(string file_path)
{
    fstream file(file_path);
    // test if file is open
    if (!file.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }
    // read data
    file >> width >> height;
    file >> start_x >> start_y;
    rooms.resize(height + 1);

    // read rooms
    for (int i = 1; i <= height; i++)
    {
        rooms[i].resize(width + 1);
        for (int j = 1; j <= width; j++)
        {
            int kind;
            bool exit_N, exit_E, exit_S, exit_W;
            file >> kind >> exit_N >> exit_E >> exit_S >> exit_W;
            rooms[i][j] = CastleRoom(kind, exit_N, exit_E, exit_S, exit_W);
        }
    }
    file.close();
    player = Player(start_x, start_y);

    // set state
    if (rooms[player.y][player.x].kind == 0)
    {
        state = 0;
    } else if (rooms[player.y][player.x].kind == 1) { // princess
        player.meet_princess = true;
        state = 1;
    } else if (rooms[player.y][player.x].kind == 2) { // monster
        state = 2;
    } else if (player.x < 1 || player.x > width || player.y < 1 || player.y > height) { // exit
        if (player.meet_princess)
            state = 3;
        else
            state = 4;
    }
}

void Castle::move(char direction)
{
    // test if direction is valid and move
    switch (direction)
    {
    case 'N':
        if (rooms[player.y][player.x].exit_N)
            player.y--;
        else
            cout << "Invalid direction!" << endl;
        break;
    case 'E':
        if (rooms[player.y][player.x].exit_E)
            player.x++;
        else
            cout << "Invalid direction!" << endl;
        break;
    case 'S':
        if (rooms[player.y][player.x].exit_S)
            player.y++;
        else
            cout << "Invalid direction!" << endl;
        break;
    case 'W':
        if (rooms[player.y][player.x].exit_W)
            player.x--;
        else
            cout << "Invalid direction!" << endl;
        break;
    }
    if (player.x < 1 || player.x > width || player.y < 1 || player.y > height) { // exit
        if (player.meet_princess) // meet princess?
            state = 3;
        else
            state = 4;
        return;
    }
    if (rooms[player.y][player.x].kind == 0)
    {
        state = 0;
    } else if (rooms[player.y][player.x].kind == 1) { // princess
        player.meet_princess = true;
        state = 1;
    } else if (rooms[player.y][player.x].kind == 2) { // monster
        state = 2;
    }
}

void Castle::print_info()
{
    // print information
    cout << "You are in a castle. There are many rooms." << endl;
    cout << "The castle size is " << width << " x " << height << "." << endl;
    cout << "You are in room (" << player.x << ", " << player.y << ")." << endl;
    cout << "There is a princess in this castle." << endl;
    cout << "You must find the princess and take her out of the castle." << endl;
    cout << "There are monsters in some rooms. If you meet a monster, you will die." << endl;
    cout << "There are exits in some rooms. If you go through an exit, you will leave the castle." << endl;
}

void Castle::print_room_prompt()
{   
    // count exits
    int num = 0;
    if (rooms[player.y][player.x].exit_N) num++;
    if (rooms[player.y][player.x].exit_E) num++;
    if (rooms[player.y][player.x].exit_S) num++;
    if (rooms[player.y][player.x].exit_W) num++;

    // print each exit with format
    cout << "There are " << num << " exits:";
    if (rooms[player.y][player.x].exit_E) {
        cout << " east";
        num --;
        if (num == 0) cout << "." << endl;
        else if (num == 1) cout << " and";
        else cout << ",";
    }
    if (rooms[player.y][player.x].exit_W) {
        cout << " west";
        num --;
        if (num == 0) cout << "." << endl;
        else if (num == 1) cout << " and";
        else cout << ",";
    }
    if (rooms[player.y][player.x].exit_N) {
        cout << " up";
        num --;
        if (num == 0) cout << "." << endl;
        else if (num == 1) cout << " and";
        else cout << ",";
    }
    if (rooms[player.y][player.x].exit_S) {
        cout << " down";
        num --;
        if (num == 0) cout << "." << endl;
        else if (num == 1) cout << " and";
        else cout << ",";
    }
    cout << "Enter your commend: " << endl;
}

void Castle::print_state()
{
    // print state
    switch (state)
    {
    case 0:
        break;
    case 1:
        // chat with princess
        cout << "You meet princess." << endl;
        cout << "You: \"My esteemed princess!\"" << endl;
        cout << "Princess: \"Thank you for saving me!\"" << endl;
        break;
    case 2:
        cout << "You meet a monster." << endl;
        cout << "Game over." << endl;
        return;
    case 3:
        cout << "You leave with princess." << endl;
        cout << "Congratulations!" << endl;
        return;
    case 4:
        cout << "You leave without princess." << endl;
        cout << "Game over." << endl;
        return;
    }
    print_room_prompt();
}


#endif