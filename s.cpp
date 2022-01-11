struct location{
    int r, c;
    int count;
}locations[10][10];
location* list[10*10+1];

int map[10][10];
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

int location_size;
int Play_map[10][10];

enum TYPE {Vacant, CAR, BAT, CRU, SUB, DES, SIZE};
int player[SIZE] = {0,5,4,3,3,2}; 
int variable[SIZE];

int GetNode(int index){
    int loc = index<<1;
    int raw = loc + 1;

    if(loc > location_size) return 0;
    if(raw > location_size) return loc;
    if(list[loc]->count < list[raw]->count) return raw;
    return loc;
}

void Move(location* state){
    list[++location_size] = state;

    int column = location_size;
    int pos = column>>1;

    while(pos && list[pos]->count < state->count){
        list[column] = list[pos];
        column = pos;
        pos = column >>1;
    }
    list[column] = state;
}



location* pop(){
    location* result = list[1];
    location* data = list[location_size--];

    int pos = 1, column;
    while((column = GetNode(pos)) && list[column]->count > data->count){
        list[pos] = list[column];

        pos = column;
    } 
    list[pos] = data;
    return result;
}


int tc;
int count;

extern int fire(int r, int c);

bool Flag(int r, int c){
    return 0 <= r && r < 10 && 0 <= c && c < 10;
}

bool Marker(int r, int c, int direction, TYPE check){
    int size = player[check];

    while(size--){
        if(Play_map[r][c] == tc || !Flag(r,c)) return false;
        r += dr[direction];
        c += dc[direction];
    }
    return true;
}

void Priority_Queue(){
    location_size = 0;
    for( int i = 0; i < 10; ++i) for( int j = 0; j < 10; ++j){
        locations[i][j].count = 0;
        locations[i][j].r = i, locations[i][j].c = j;
        for(int k = 1; k < SIZE;++k){
            if(variable[k] == tc) continue;
            for(int d = 0; d < 4; ++d){if(Marker(i,j,d,(TYPE)k)) locations[i][j].count+= 10000 - player[k];
            }
        }
        if(locations[i][j].count) Move(locations[i] + j);
    }
}

void init(int limit) { }

bool Chess(location* position, TYPE Monopoly){
    TYPE Case1, Case2;
    int d;
    if(Monopoly == Vacant) Case1 = (TYPE)fire(position->r, position->c), Play_map[position->r][position->c] = tc;
    else Case1= Monopoly;
    
    int nr, nc;
    int Trasher = player[Case1]-1;
    int Visual = 0;
    int r = position->r, c= position->c;
    int tx[SIZE] , ty[SIZE];
    count -= (bool)Case1;

    if(Case1) {
        Case2 = Case1;
        variable[Case1] = tc;
        for(d = 0; d < 4; ++d){
            nr = r+dr[d], nc = c + dc[d];
            while(Flag(nr,nc) && Play_map[nr][nc] != tc && Trasher && (Case2 = (TYPE)fire(nr,nc)) == Case1){
                count--;
                Play_map[nr][nc] = tc;
                Trasher--;
                nr+=dr[d], nc += dc[d];
            }
            Visual |= (1<<Case2);
            if(Case2 && Case1 != Case2) tx[Case2] = nr, ty[Case2] = nc;

            if(d<2 && Trasher +1 != player[Case1]){
                d += 2;
                nr = r + dr[d], nc = c + dc[d];

                while(Trasher && fire(nr,nc)){
                    count--;
                    Play_map[nr][nc] = tc;
                    Trasher--;
                    nr += dr[d], nc += dc[d];
                }
            } 

            if(!Trasher){
                for(int i = 1; i < SIZE; ++i){
                    if(i != Case1 && Visual & (1<<i)){
                        Chess(locations[tx[i]]+ty[i], (TYPE)i);
                    }
                }
                return true;
            } 
        }
    }
    return false;
}

void play()
{   location* position;
    ++tc;
    count = 17;
    while(count) while(Priority_Queue(), position = pop(), !Chess(position, Vacant));
}