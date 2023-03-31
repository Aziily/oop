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
        int kind;
        bool exit_N, exit_E, exit_S, exit_W;
        CastleRoom() {}
        CastleRoom(int kind, bool exit_N, bool exit_E, bool exit_S, bool exit_W) \
            : kind(kind), exit_N(exit_N), exit_E(exit_E), exit_S(exit_S), exit_W(exit_W) {}
    };
    struct Player
    {
        int x, y;
        bool meet_princess;
        Player() {}
        Player(int x, int y, bool meet_princess=false) \
            : x(x), y(y), meet_princess(meet_princess) {}
    };
    
private:
    vector<vector<CastleRoom>> rooms;
    int width, height;
    int start_x, start_y;
    Player player;
    int state;

public:
    Castle(string file_path);
    ~Castle();
    void move(char direction);
    int get_state() { return state; }
    void print_room_prompt();
    void print_state();
};

Castle::Castle(string file_path)
{
    fstream file(file_path);
    if (!file.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }
    file >> width >> height;
    file >> start_x >> start_y;
    rooms.resize(height + 1);
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

Castle::~Castle()
{
    delete this;
}

void Castle::move(char direction)
{
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

void Castle::print_room_prompt()
{   
    int num = 0;
    if (rooms[player.y][player.x].exit_N) num++;
    if (rooms[player.y][player.x].exit_E) num++;
    if (rooms[player.y][player.x].exit_S) num++;
    if (rooms[player.y][player.x].exit_W) num++;

    cout << "There are " << num << " exits:" << endl;
    if (rooms[player.y][player.x].exit_E) {
        cout << " east" << endl;
        num --;
        if (num == 0) cout << "." << endl;
        else if (num == 1) cout << " and" << endl;
        else cout << "," << endl;
    }
    if (rooms[player.y][player.x].exit_W) {
        cout << " west" << endl;
        num --;
        if (num == 0) cout << "." << endl;
        else if (num == 1) cout << " and" << endl;
        else cout << "," << endl;
    }
    if (rooms[player.y][player.x].exit_N) {
        cout << " up" << endl;
        num --;
        if (num == 0) cout << "." << endl;
        else if (num == 1) cout << " and" << endl;
        else cout << "," << endl;
    }
    if (rooms[player.y][player.x].exit_S) {
        cout << " down" << endl;
        num --;
        if (num == 0) cout << "." << endl;
        else if (num == 1) cout << " and" << endl;
        else cout << "," << endl;
    }
    cout << "Enter your commend: " << endl;
}

void Castle::print_state()
{
    switch (state)
    {
    case 0:
        break;
    case 1:
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
