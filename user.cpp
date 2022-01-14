#define INF 100000
#define MAX_HASH 100000
#define MAX_NAME 20
#define MAX_MEMBER 200

int mstrcmp(const char *a, const char *b)
{
    int i;
    for (i = 0; a[i] != '\0'; ++i) {
        if (a[i] != b[i]) {
            return a[i] - b[i];
        }
    }
    return a[i] - b[i];
}

void mstrcpy(char *dest, const char *src)
{
    int i{0};
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
}


enum Sex { MALE, FEMALE, MERGED };
enum Relation { SPOUSE, PARENT, CHILD };

struct Member {
    Sex sex;
    int id;
    int d{INF};
    int Count_Children{0};
    char Male_Name[MAX_NAME];
    char FEMALE_Name[MAX_NAME];
    Member *MALE_Parents{nullptr};
    Member *FEMALE_Parents{nullptr};
    Member *CHILD[MAX_MEMBER - 1]{};

    Member() {}
    Member(const char *name, Sex sex, int id) : sex{sex}, id{id}
    {
        mstrcpy(sex == MALE ? Male_Name : FEMALE_Name, name);
    }
} Size[MAX_MEMBER];


unsigned HASH(const char *a)
{
    unsigned Value{0};
    while (*a) {
        Value = *a++ + 31 * Value;
    }
    return Value;
}

bool FLAG{false};
int member_count{0};

int distance[MAX_MEMBER][MAX_MEMBER];

Member *name_table[MAX_HASH];
Sex sex_table[MAX_HASH];
void Insert(Member *member, Sex sex)
{
    unsigned hash_value{HASH(sex == MALE ? member->Male_Name : member->FEMALE_Name) %
                  MAX_HASH};
    while (true) {
        if (!name_table[hash_value]) {
            name_table[hash_value] = member;
            sex_table[hash_value] = sex;
            break;
        }
        hash_value = (hash_value + 1) % MAX_HASH;
    }
}
Member *Allocation(const char *name, Sex sex)
{
    Member *m{&Size[member_count]};
    *m = Member(name, sex, member_count++);
    Insert(m, sex);
    return m;
}

void NickName(Member *member, const char *name)
{
    const Sex sex{member->sex == MALE ? FEMALE : MALE};
    member->sex = MERGED;
    mstrcpy(sex == MALE ? member->Male_Name : member->FEMALE_Name, name);
    Insert(member, sex);
}
Member *UpperSide(const char *name, Sex *sex = nullptr)
{
    unsigned hash_value{HASH(name) % MAX_HASH};
    Member *m{nullptr};
    do {
        unsigned next{(hash_value + 1) % MAX_HASH};
        if (!name_table[next]) {
            m = name_table[hash_value];
            if (sex) {
                *sex = sex_table[hash_value];
            }
        } else if (mstrcmp(sex_table[hash_value] == MALE ? name_table[hash_value]->Male_Name : name_table[hash_value]->FEMALE_Name,name) == 0) {
            m = name_table[hash_value];
            if (sex) {
                *sex = sex_table[hash_value];
            }
        } else {
            hash_value = next;
        }
    } while (!m);
    return m;
}

struct Node_Member {
    Member *member;
    Node_Member *next;
} Node_Members[MAX_MEMBER];

int node_count{0};
Node_Member *head{nullptr};
Node_Member *tail{nullptr};
inline bool empty() { return !head; }
inline void init_queue()
{
    head = tail = nullptr;
    node_count = 0;
}

Node_Member *Allocation(Member *member, Node_Member *next = nullptr)
{
    Node_Member *n{&Node_Members[node_count++]};
    *n = {member, next};
    return n;
}

void enqueue(Member *member)
{
    if (!tail) {
        head = tail =Allocation(member);
        return;
    }
    tail->next = Allocation(member);
    tail = tail->next;
}

Member *dequeue()
{
    Member *m{head->member};
    head = head->next;
    if (!head) {
        tail = nullptr;
    }
    return m;
}

void Visit_Node(Member *member, int d)
{
    if (!member || member->d < INF) {
        return;
    }
    member->d = d + 1;
    enqueue(member);
}

void init(char initialMemberName[], int initialMemberSex)
{
    for (int i{0}; i < MAX_HASH; ++i) {
        name_table[i] = nullptr;
    }
    member_count = 0;
  Allocation(initialMemberName, static_cast<Sex>(initialMemberSex));
}

bool addMember(char newMemberName[], int newMemberSex, int relationship,
               char existingMemberName[])
{
    Sex sex;
    Member *member{UpperSide(existingMemberName, &sex)};
    const Sex new_sex{static_cast<Sex>(newMemberSex)};

    switch (relationship) {
    case PARENT: {
        Member *parents{sex == MALE ? member->MALE_Parents : member->FEMALE_Parents};
        if (parents) {
            if (parents->sex == MERGED || parents->sex == new_sex) {
                return false;
            }
            NickName(parents, newMemberName);
        } else {
            parents =Allocation(newMemberName, new_sex);
            parents->CHILD[parents->Count_Children++] = member;
            (sex == MALE ? member->MALE_Parents : member->FEMALE_Parents) = parents;
            FLAG = true;
        }
    } break;  
    case CHILD: {
        Member *child{member->CHILD[member->Count_Children++] =
                        Allocation(newMemberName, new_sex)};
        (new_sex == MALE ? child->MALE_Parents : child->FEMALE_Parents) = member;
        FLAG = true;
    } break;
    case SPOUSE:
        if (new_sex == member->sex || member->sex == MERGED) {
            return false;
        }
        NickName(member, newMemberName);
        break;
    }
    return true;
}

void bfs(int id)
{
    Member *src{&Size[id]};
    init_queue();
    for (int i{0}; i < member_count; ++i) {
        Size[i].d = INF;
    }
    src->d = 0;
    enqueue(src);

    int count{0};
    while (!empty()) {
        Member *m{dequeue()};
        distance[id][m->id] = m->d;
        Visit_Node(m->MALE_Parents, m->d);
        Visit_Node(m->FEMALE_Parents, m->d);
        for (int i{0}; i < m->Count_Children; ++i) {
            Visit_Node(m->CHILD[i], m->d);
        }
    }
}

void update()
{
    for (int i{0}; i < member_count; ++i) {
        bfs(i);
    }
}

int getdistance(char nameA[], char nameB[])
{
    if (FLAG) {
        update();
        FLAG = false;
    }
    return distance[UpperSide(nameA)->id][UpperSide(nameB)->id];
}

int countMember(char name[], int dist)
{
    if (FLAG) {
        update();
        FLAG = false;
    }
    const int id{UpperSide(name)->id};
    int count{0};
    for (int i{0}; i < member_count; ++i) {
        if (distance[id][i] == dist) {
            count += Size[i].sex == MERGED ? 2 : 1;
        }
    }
    return dist == 0 ? count - 1 : count;
}