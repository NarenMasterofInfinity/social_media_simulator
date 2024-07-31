#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <stack>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <list>
#include <queue>
#include <limits.h>
#include <ctime>
#include <cmath>
#include <unordered_map>
#include <unistd.h>
// #include "D:\4th sem\ADS Lab\Complete_project1(copy)\conv_db.hpp"

#ifndef CLASSES_H
#define CLASSES_H

using namespace std;

#define POST_MAX 8  // 128
#define USER_MAX 8  // 512
#define COMM_MAX 8  // 512
#define LIKE_MAX 8  // 1024
#define SHARE_MAX 8 // 256
#define VIEW_MAX 8  // 2048
#define TAG_MAX 8   // 32
#define GROUP_MAX 8 // 16
#define MAX_C 10    // 1024
#define NORMAL_CONV 'n'
#define GROUP_CONV 'g'
#define COMMUNITY_CONV 'c'
#define TEXT_MSG "t"
#define IMAGE_MSG "i"
#define VIDEO_MSG "v"
#define AUDIO_MSG "a"
#define POST_MSG "p"
#define REPORTS_MAX 5
#define TREND_MAX 1024
#define FRIENDS_MAX 1024
#define M_PI 3.14159265358979323846
#define INF numeric_limits<double>::infinity()

class Post;
class User;
class Conversation;
class DMConversation;
class GroupConversation;
class CommunityConversation;
class RequestBasedCommunity;
class FreeJoinCommunity;
class Message;
class Multimedia;
class Video;
class Audio;
template <typename T>
class Text;
class Story;
class Gif;
class Image;
class Group;
class Comment;
class String;
class Notification;
class Emoji;
template <typename T>
class Node;
template <typename T>
class AVLTree;
template <typename T>
class Snode;
template <typename T>
class SplayTree;
template <typename T>
class HeapTree;
class Graph;
class Edge;
class UndirectedGraph;
template <typename T>
class post_AVLNode;
template <typename T>
class post_AVLTree;
template <typename T, typename U>
class post_Graph;
class post_PostGraph;
template <typename T>
class post_heap;
class post_DisjointSet;
template <typename T>
class post_SplayNode;
template <typename T>
class post_SplayTree;
template <typename T>
class MM_Post;
class Message_Post;
class Poll;

// post_PostGraph graph;

// defining emojis
map<string, string> emojis = {
    {"happy", "😊"},
    {"heart_eyes", "😍"},
    {"smile", "😁"},
    {"laugh", "😂"},
    {"cry", "😢"},
    {"angry", "😡"},
    {"surprised", "😮"},
    {"confused", "😕"},
    {"kiss", "😘"},
    {"sick", "🤢"},
    {"cool", "😎"},
    {"sleep", "😴"},
    {"worried", "😟"},
    {"sad", "😔"},
    {"unamused", "😒"},
    {"blush", "😊"},
    {"hug", "🤗"},
    {"wink", "😉"},
    {"grin", "😁"},
    {"tongue", "😋"},
    {"neutral", "😐"},
    {"smirk", "😏"},
    {"relieved", "😌"},
    {"pensive", "😔"},
    {"confounded", "😖"},
    {"disappointed", "😞"},
    {"persevere", "😣"},
    {"sweat", "😅"},
    {"weary", "😩"},
    {"sob", "😭"},
    {"joy", "😂"},
    {"scream", "😱"},
    {"rage", "😠"},
    {"yum", "😋"},
    {"demon", "😈"},
    {"demon_smile", "👿"},
    {"innocent", "😇"},
    {"clown", "🤡"},
    {"lying", "🤥"},
    {"shushing", "🤫"},
    {"thinking", "🤔"},
    {"zipper", "🤐"},
    {"eye_roll", "🙄"},
    {"sunglasses", "😎"},
    {"nerd", "🤓"},
    {"sick", "🤒"},
    {"bandage", "🤕"},
    {"thermometer", "🌡️"},
    {"sneezing", "🤧"},
    {"mask", "😷"},
    {"vomit", " 🤮"},
    {"bull", "🐂"},
    {"polarbear", "🐻‍❄️"},
    {"panda", "🐼"},
    {"mushroom", "🍄"},
    {"monkey", "🐒"},
    {"duck", "🦆"}

};

map<string, int> mui;
map<int, string> miu;
map<string, int> muiUG;
map<int, string> miuUG;
map<Conversation *, int> mciUGComm;
map<int, Conversation *> micUGComm;
vector<map<int, Post *>> mip;
vector<map<Post *, int>> mpi;

int explanationPostPtr = 0;

string timetostring(time_t timeValue)
{
    return ctime(&timeValue);
}

template <typename T>
void swap(T *a, T *b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}
int lcsuser(string user1, string user2)
{
    int m = user1.length();
    int n = user2.length();
    int dp[m + 1][n + 1];
    for (int i = 0; i < m + 1; i++)
    {
        dp[i][0] = 0;
    }
    for (int i = 0; i < n + 1; i++)
    {
        dp[0][i] = 0;
    }

    for (int i = 1; i < m + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            if (user1[i - 1] == user2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}
bool sortingfn(pair<int, int> p1, pair<int, int> p2)
{
    return p1.second > p2.second;
}
void setSession(int *session)
{
    *session = 1;
}

void change_to_lowercase(string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = s[i] - 'A' + 'a';
        }
    }
}
void banner_display_util()
{
    int retcode = system("figlet SNAHPYN SOCIETY");
    cout << endl;
}
void banner_display()
{
    cout << "Welcome To" << endl;
    banner_display_util();
    int retcode = system("echo '\e[3mSnahpyn Whats Happenin!\e[0m'");
    cout << "==================================================" << endl;
}
User *current_user = nullptr;

double epsilon = 1e-5; // for numerical stability

class Graph
{
public:
    int nv;
    vector<vector<int>> adj;
    Graph()
    {
        nv = 0;
    }
    Graph(int nv)
    {
        this->nv = nv;

        for (int i = 0; i < nv; i++)
        {
            for (int j = 0; j < nv; j++)
            {
                adj[i][j] = 0;
            }
        }
    }
    void init_adj();

    void bfs(User *);

    void bfslevelutil(int, vector<User> &, int); // in user_methods.hpp
    void addEdge(User *, User *);
    void addEdgeUtil(int, int);
    void addVertex();
    void bfsutil(int);
    void dfs();
    void dfsutil(int, bool[]);
    void addPostVertex(int, Post *);
    void addPostEdge(int, Post *, Post *);

    void addEdgeComment(Comment *, Comment *, Post *);
    void addEdgeUtilComment(int, int, int);
    void addVertexComment();
    void dfsComment(Post *);
    void dfsutilComment(int, bool[], Post *, int);
    vector<Comment *> topologicalSort(Post *);
    void topologicalSortUtil(int, vector<bool> &, Post *, vector<int> &);
    void topologicalSortUtilForPost(int, vector<bool> &, vector<int> &);
    vector<Post *> topologicalSortForPost(int);
};

Graph *global_users = new Graph;
int num_users = 0;

void display_all_users()
{
    global_users->dfs();
}
template <typename T>
class HeapTree
{
    int left(int i);
    int right(int i);
    int parent(int i);
    void swap(T *, T *);

public:
    vector<T> arr;
    vector<T> copy;
    HeapTree() {}
    void heapify(int, vector<T> &);
    void insert(T val);
    void sorted_display();
    T extract_max(vector<T> &);
    void delete_node(T val);
    void delete_element(int);
    T search(int);
};

template <typename T>
class Snode
{
public:
    Snode<T> *right, *left, *p;
    T val;
    Snode()
    {
        right = left = p = nullptr;
    }
    Snode(T val)
    {
        this->val = val;
        right = left = p = nullptr;
    };
};

template <typename T>
class SplayTree
{
public:
    Snode<T> *root;
    SplayTree()
    {
        root = nullptr;
    };
    void insert_node(T);
    void left_rotate(Snode<T> *);
    void right_rotate(Snode<T> *);
    void inorder(Snode<T> *);
    // T search_node(Snode <T>*)
    void splay_up(Snode<T> *);
    Snode<T> *zig(Snode<T> *);
    Snode<T> *zag(Snode<T> *);
    Snode<T> *inorder_successor(Snode<T> *);
    void delete_node(T);
    void peekRoot();
};
template <typename T>
class Node
{
public:
    T val;
    int height;
    Node<T> *right, *left;
    Node(T val)
    {
        this->val = val;
        right = left = nullptr;
        height = 0;
    }
};

template <typename T>
class AVLTree
{
public:
    Node<T> *root;
    AVLTree()
    {
        root = nullptr;
    }
    Node<T> *insert_node(Node<T> *, T);
    Node<T> *left_rotate(Node<T> *);
    Node<T> *right_rotate(Node<T> *);
    Node<T> *parent(Node<T> *, Node<T> *);
    void inorder(Node<T> *);
    Node<T> *delete_node(Node<T> *, T);
    void update_node(Node<T> *, T);
    Node<T> *search(Node<T> *, T);
    Node<T> *minimum(Node<T> *);
    void getmsgs(Node<T> *, list<Message *> &);
    void getusers(Node<T> *, vector<User> &);
    int size(Node<T> *);
    void inorder_no_pointer(Node<T> *);
};

template <typename T>
class post_heap
{
public:
    T *min_arr;
    T *max_arr;
    T *sorted_arr;
    int size = TREND_MAX;
    int top;

    post_heap()
    {
        min_arr = new T[TREND_MAX];
        max_arr = new T[TREND_MAX];
        sorted_arr = new T[TREND_MAX];
        top = 0;
    }

    void max_heapify(int i)
    {
        int largest = i;
        int left = (2 * i) + 1;
        int right = (2 * i) + 2;

        if (left < top && max_arr[left]->tf > max_arr[largest]->tf)
        {
            largest = left;
        }

        if (right < top && max_arr[right]->tf > max_arr[largest]->tf)
        {
            largest = right;
        }

        if (largest != i)
        {
            swap(&max_arr[largest], &max_arr[i]);
            min_heapify(largest);
        }
    }

    void min_heapify(int i)
    {
        int smallest = i;
        int left = (2 * i) + 1;
        int right = (2 * i) + 2;

        if (left < top && min_arr[left]->tf < min_arr[smallest]->tf)
        {
            smallest = left;
        }

        if (right < top && min_arr[right]->tf < min_arr[smallest]->tf)
        {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(&min_arr[smallest], &min_arr[i]);
            min_heapify(smallest);
        }
    }

    void insert(T num)
    {
        if (top == size)
        {
            cout << "Heap size exceeded" << endl;
            return;
        }
        min_arr[top] = num;
        max_arr[top] = num;
        top++;

        for (int i = (top / 2) - 1; i >= 0; i--)
        {
            min_heapify(i);
            max_heapify(i);
        }
    };

    void make_heap()
    {
        for (int i = top - 1; i >= 0; i--)
        {
            min_heapify(i);
            max_heapify(i);
        }
    }

    void del()
    {
        if (top == 0)
        {
            cout << "No element to delete" << endl;
            return;
        }
        swap(&min_arr[0], &min_arr[top - 1]);
        swap(&max_arr[0], &max_arr[top - 1]);
        top--;
        for (int i = top - 1; i >= 0; i--)
        {
            min_heapify(i);
            max_heapify(i);
        }
    }

    void min_display()
    {
        if (top == 0)
        {
            cout << "No element to display" << endl;
            return;
        }
        for (int i = 0; i < top; i++)
        {
            cout << min_arr[i] << " ";
        }
        cout << endl;
    }

    void max_display()
    {
        if (top == 0)
        {
            cout << "No element to display" << endl;
            return;
        }
        for (int i = 0; i < top; i++)
        {
            cout << max_arr[i]->PID << " Tf: " << max_arr[i]->tf << " ";
        }
        cout << endl;
    }

    void heapify(int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < top && sorted_arr[left]->tf > sorted_arr[largest]->tf)
            largest = left;

        if (right < top && sorted_arr[right]->tf > sorted_arr[largest]->tf)
            largest = right;

        if (largest != i)
        {
            swap(&sorted_arr[i], &sorted_arr[largest]);
            heapify(largest);
        }
    }

    void heapSort()
    {
        for (int i = 0; i < top; i++)
        {
            sorted_arr[i] = max_arr[i];
        }
        for (int i = (top / 2) - 1; i >= 0; i--)
            heapify(i);

        for (int i = top - 1; i >= 0; i--)
        {
            swap(&sorted_arr[0], &sorted_arr[i]);
            heapify(i);
        }
    }

    void display()
    {
        heapSort();
        for (int i = 0; i < top; i++)
        {
            cout << sorted_arr[i]->PID << " Tf: " << sorted_arr[i]->tf << " ";
        }
        cout << endl;
    }
};

post_heap<Post *> trending;

class post_PostGraph
{
private:
    map<string, list<string>> adjacencyList;

public:
    void addPost(string author, string postID)
    {
        adjacencyList[author].push_back(postID);
    }

    void DFS(string startVertex)
    {
        int j = 1;
        map<string, bool> visited;
        for (const auto &pair : adjacencyList)
        {
            visited[pair.first] = false;
        }

        list<string> stack;

        visited[startVertex] = true;
        stack.push_back(startVertex);

        while (!stack.empty())
        {
            string currUser = stack.back();
            stack.pop_back();

            for (const string &postID : adjacencyList[currUser])
            {
                cout << postID << endl;
            }

            for (const string &adjUser : adjacencyList[currUser])
            {
                if (!visited[adjUser])
                {
                    visited[adjUser] = true;
                    stack.push_back(adjUser);
                }
            }
        }
        cout << endl;
    }
};

post_PostGraph graph;

template <typename T, typename U>
class post_Graph
{
public:
    int numVertices;
    map<T, list<U>> adjLists;
    bool *visited;

    post_Graph(int vertices)
    {
        numVertices = vertices;
    }

    void addNode(T src)
    {
        adjLists[src].push_back("None");
    }

    void addEdge(T src, U dest)
    {
        adjLists[src].push_back(dest);
        adjLists[dest].push_back(src);
    }

    void floydWarshall()
    {
        map<T, map<T, double>> dist;
        for (const auto &pair : adjLists)
        {
            T u = pair.first;
            dist[u][u] = 0.0;
            for (const U &v : pair.second)
            {
                if (v != "None")
                {
                    dist[u][v] = 1.0;
                }
            }
        }

        for (const auto &pair1 : adjLists)
        {
            for (const auto &pair2 : adjLists)
            {
                if (dist[pair1.first].find(pair2.first) == dist[pair1.first].end())
                {
                    dist[pair1.first][pair2.first] = INF;
                }
            }
        }

        for (const auto &k_pair : adjLists)
        {
            T k = k_pair.first;
            for (const auto &i_pair : adjLists)
            {
                T i = i_pair.first;
                for (const auto &j_pair : adjLists)
                {
                    T j = j_pair.first;
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        for (const auto &from_pair : dist)
        {
            for (const auto &to_pair : from_pair.second)
            {
                // cout << "Shortest path from " << from_pair.first << " to " << to_pair.first << " is ";
                cout << "(" << from_pair.first << " , " << to_pair.first << "): ";
                if (to_pair.second == INF)
                {
                    cout << "INF";
                }
                else
                {
                    cout << to_pair.second;
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    void BFS(T startVertex)
    {
        int j = 1;
        map<T, bool> visited;
        for (const auto &pair : adjLists)
        {
            visited[pair.first] = false;
        }

        list<T> queue;

        visited[startVertex] = true;
        queue.push_back(startVertex);

        typename map<T, list<U>>::iterator i;

        while (!queue.empty())
        {
            T currVertex = queue.front();
            if (j != 1)
                cout << currVertex << " ";
            queue.pop_front();

            for (const U &adjVertex : adjLists[currVertex])
            {
                if (!visited[adjVertex])
                {
                    visited[adjVertex] = true;
                    queue.push_back(adjVertex);
                }
            }
            j++;
        }
        cout << endl;
    }
};

post_Graph<string, string> allusers(USER_MAX);
post_Graph<string, string> friends(FRIENDS_MAX);

template <typename T>
class post_SplayNode
{
public:
    T data;
    post_SplayNode<T> *left, *right;

    post_SplayNode(T data) : data(data), left(nullptr), right(nullptr) {}
};

template <typename T>
class post_SplayTree
{
private:
    post_SplayNode<T> *root;

    post_SplayNode<T> *rightRotate(post_SplayNode<T> *x)
    {
        post_SplayNode<T> *y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    post_SplayNode<T> *leftRotate(post_SplayNode<T> *x)
    {
        post_SplayNode<T> *y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    post_SplayNode<T> *splay(post_SplayNode<T> *root, T key)
    {
        if (root == nullptr || root->data == key)
            return root;

        if (root->data > key)
        {
            if (root->left == nullptr)
                return root;

            if (root->left->data > key)
            {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            }
            else if (root->left->data < key)
            {
                root->left->right = splay(root->left->right, key);

                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }

            return (root->left == nullptr) ? root : rightRotate(root);
        }
        else
        {
            if (root->right == nullptr)
                return root;

            if (root->right->data < key)
            {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            }
            else if (root->right->data > key)
            {
                root->right->left = splay(root->right->left, key);

                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            }

            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

    post_SplayNode<T> *insert(post_SplayNode<T> *root, T key)
    {
        if (root == nullptr)
            return new post_SplayNode<T>(key);

        root = splay(root, key);

        if (root->data == key)
            return root;

        post_SplayNode<T> *newNode = new post_SplayNode<T>(key);

        if (root->data > key)
        {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        }

        else
        {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }

        return newNode;
    }

    post_SplayNode<T> *search(post_SplayNode<T> *root, T key)
    {
        return splay(root, key);
    }

    void preOrderUtil(post_SplayNode<T> *root)
    {
        if (root != nullptr)
        {
            cout << root->data->PID << " ";
            preOrderUtil(root->left);
            preOrderUtil(root->right);
        }
    }

public:
    post_SplayTree() : root(nullptr) {}

    void insert(T key)
    {
        root = insert(root, key);
    }

    bool search(T key)
    {
        root = search(root, key);
        return (root != nullptr && root->data == key);
    }

    void preOrder()
    {
        preOrderUtil(root);
    }
};

class Comment
{
    string content;
    Post *belongs_to;

public:
    int no_of_likes;
    User *author;
    User *likes[LIKE_MAX];
    time_t time_of_creation;
    User *replied_to;

    Comment()
    {
        no_of_likes = 0;
        time_of_creation = time(NULL);
    }
    Comment(User *author, string content)
    {
        this->author = author;
        this->content = content;
        time_of_creation = time(NULL);
    }
    ~Comment()
    {
    }

    void DisplayComment(int, Post *);
    void display();
};

class User
{
    string username, bio, password, email;
    Image *profile_picture;

public:
    vector<User *> Following;
    vector<User *> Followers;
    HeapTree<Notification> notifications;
    vector<Story> myStories;
    int change;
    vector<Post *> my_posts;
    vector<Post *> saved_posts;
    post_SplayTree<Post *> *viewed_posts; // post_splay
    int saved_ptr, post_ptr;
    list<Story> my_stories;
    vector<int> viewed_stories;
    list<Post *> reports;
    int post_num;
    int num_flw;
    int num_flg;
    User()
    {
        username = bio = password = "";
        post_num = 0;
        num_flg = num_flw = 0;
        viewed_posts = new post_SplayTree<Post *>();
    }

    User(string username, string password, string email)
    {
        saved_ptr = 0;
        this->username = username;
        this->email = email;
        this->password = password;
        post_num = 0;
        viewed_posts = new post_SplayTree<Post *>();
        allusers.addNode(this->getUsername());
        num_flg = num_flw = 0;
    }

    User(string username)
    {
        viewed_posts = new post_SplayTree<Post *>();
        saved_ptr = 0;
        this->username = username;
        post_num = 0;
        allusers.addNode(this->getUsername());
        num_flg = num_flw = 0;
    }

    User(User *user)
    {
        viewed_posts = new post_SplayTree<Post *>();
        saved_ptr = 0;
        this->password = user->getPassword();
        this->email = user->getEmail();
        this->username = user->getUsername();
        post_num = 0;
        allusers.addNode(this->getUsername());
        num_flg = num_flw = 0;
    }
    User(const User &other)
    {
        viewed_posts = new post_SplayTree<Post *>();
        this->username = other.username;
        this->email = other.email;
        this->password = other.password;
        this->myStories = other.myStories;
        this->profile_picture = other.profile_picture;
        this->notifications = other.notifications;
        this->bio = other.bio;
        this->saved_posts = other.saved_posts;
        this->my_posts = other.my_posts;
        post_num = 0;
        num_flg = num_flw = 0;
    }
    ~User()
    {
    }

    void view_post(Post *post)
    {
        viewed_posts->insert(post);
    }

    void recently_viewed_posts()
    {
        cout << "Recently Viewed Posts by " << username << ":\n";
        viewed_posts->preOrder();
        cout << endl;
    }

    void follow_user(User *name)
    {
        Following.push_back(name);
        this->num_flg++;
        name->Followers.push_back(this);
        name->num_flw++;
        allusers.addEdge(this->getUsername(), name->getUsername());
    }

    void create_post();
    // void create_MM_Post();
    void interact_post(Post *);
    void share_post(Post *, User *);
    void share_post(Post *, User *, User *);
    void sendNotification(User *to, Conversation *forconv, string content);

    void setUsername(string);
    void setEmail(string);
    void setPassword(string);
    void display_profile(int);
    void feed_recommendation();
    Conversation *createDMConversation();
    Conversation *createCommunityConversation();
    void display_friend_suggestions();
    void adminWorkOnRBCommunity(Conversation *);

    string getUsername();
    string getEmail();
    string getPassword();

    static User *search_user(string);

    static User search_user_no_pointer(string);

    void display_friends();
    void sendNotification(string, string, float);
    void displayStories();
    void displayNotifications();
    static pair<bool, string> login();
    static User *register_user();
    void show_saved_post();
    void operator+(Post *);
    bool operator<(User);
    bool operator<=(User);
    Conversation *createGroup();
    bool operator>(User);
    bool operator>=(User);
    bool operator==(User);
    bool operator!=(User);
    static void display(User);
    static void display(User, bool);

    void addFriend(User *);
    void display()
    {
        cout << username << endl;
    }
    // friend functions

    // friend bool operator>(User, User);
};

vector<Post *> allPosts;
queue<Post *> rep_posts;

class Post
{
    string content;

public:
    Video *post_video;
    Image *post_image;
    int ptype;
    string PID;
    Graph *Comments;
    map<Comment *, int> CommentToInteger;
    map<int, Comment *> IntegerToComment;
    int comment_ptr;
    int no_of_likes;
    list<User *> Likes;
    // User *Likes[LIKE_MAX];
    time_t time_of_creation;
    // User *Shares[SHARE_MAX]; //not useful ig
    int no_of_shares;
    // string location;
    User *author;
    int reports;
    stack<User *> rep_users;
    int tf;
    pair<double, double> location;
    Post()
    {
        post_video = nullptr;
        post_image = nullptr;
        Comments = new Graph();
        comment_ptr = 0;
        no_of_likes = no_of_shares = 0;
        content = "";
        reports = 0;
        time_of_creation = time(NULL);
        tf = 0;
        trending.insert(this);
        location = make_pair(0, 0);
        // cout << "Post created" << endl;
    }
    /*
    Post(Post &p)
    {
        this->no_of_likes = p.no_of_likes;
        this->location = p.location;
        this->content = p.content;
        this->time_of_creation = p.time_of_creation;
        this->content = p.content;
    }
    */
    Post(string content, User *author)
    {
        post_video = nullptr;
        post_image = nullptr;
        Comments = new Graph();
        comment_ptr = 0;
        no_of_likes = no_of_shares = 0;
        reports = 0;
        this->author = author;
        setContent(content);
        ptype = 0;
        time_of_creation = time(NULL);
        int time = time_of_creation;
        this->author->post_num++;
        this->PID = author->getUsername() + "_" + to_string(time) + "_" + to_string(this->author->post_num);
        tf = 0;
        trending.insert(this);
        graph.addPost(this->author->getUsername(), this->PID);
        location = make_pair(0, 0);
    }

    Post(string content, User *author, double latitude, double longitude)
    {
        post_video = nullptr;
        post_image = nullptr;
        ptype = 0;
        Comments = new Graph();
        comment_ptr = 0;
        no_of_likes = no_of_shares = 0;
        reports = 0;
        this->author = author;
        setContent(content);
        time_of_creation = time(NULL);
        int time = time_of_creation;
        this->author->post_num++;
        this->PID = author->getUsername() + "_" + to_string(time) + "_" + to_string(this->author->post_num);
        tf = 0;
        trending.insert(this);
        graph.addPost(this->author->getUsername(), this->PID);
        location = make_pair(latitude, longitude);
        allPosts.push_back(this);
    }

    Post(string content, User *author, double latitude, double longitude, Image *I)
    {
        post_video = nullptr;
        post_image = I;
        Comments = new Graph();
        comment_ptr = 0;
        no_of_likes = no_of_shares = 0;
        reports = 0;
        ptype = 1;
        this->author = author;
        setContent(content);
        time_of_creation = time(NULL);
        int time = time_of_creation;
        this->author->post_num++;
        this->PID = author->getUsername() + "_" + to_string(time) + "_" + to_string(this->author->post_num);
        tf = 0;
        trending.insert(this);
        graph.addPost(this->author->getUsername(), this->PID);
        location = make_pair(latitude, longitude);
        allPosts.push_back(this); // needs to be checked
    }

    Post(string content, User *author, double latitude, double longitude, Video *V)
    {
        post_video = V;
        post_image = nullptr;
        Comments = new Graph();
        comment_ptr = 0;
        no_of_likes = no_of_shares = 0;
        reports = 0;
        ptype = 2;
        this->author = author;
        setContent(content);
        time_of_creation = time(NULL);
        int time = time_of_creation;
        this->author->post_num++;
        this->PID = author->getUsername() + "_" + to_string(time) + "_" + to_string(this->author->post_num);
        tf = 0;
        trending.insert(this);
        graph.addPost(this->author->getUsername(), this->PID);
        location = make_pair(latitude, longitude);
        allPosts.push_back(this);
    }

    double calculateDistance(const Post &otherPost) const
    {
        const double earthRadius = 6371.0;
        double lat1 = location.first;
        double lon1 = location.second;
        double lat2 = otherPost.location.first;
        double lon2 = otherPost.location.second;
        double dLat = (lat2 - lat1) * M_PI / 180.0;
        double dLon = (lon2 - lon1) * M_PI / 180.0;
        double a = sin(dLat / 2.0) * sin(dLat / 2.0) +
                   cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
                       sin(dLon / 2.0) * sin(dLon / 2.0);
        double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
        double distance = earthRadius * c;
        return distance;
    }

    ~Post()
    {
        // delete Comments;
    }

    string getContent()
    {
        return content;
    }

    void setContent(string cont)
    {
        this->content = cont;
    }

    void update_tf()
    {
        this->tf = no_of_likes + no_of_shares;
        trending.make_heap();
    }
    void display_post_details();

    // void edit_post(){
    //     no_of_likes = no_of_shares = 0;
    //     string ncon;
    //     cout<<"Enter the Content for the edited post: ";
    //     cin.ignore();
    //     getline(cin,ncon);
    //     setContent(ncon);
    //     cout<<"Post has been modified with new text"<<endl;
    // };

    void showlikesasc()
    {
        if (Likes.empty())
        {
            cout << "No likes yet" << endl;
        }
        else
        {
            cout << "No of Likes: " << no_of_likes << endl;
            cout << "Liked by: " << endl;
            for (list<User *>::iterator it = Likes.begin(); it != Likes.end(); ++it)
            {
                cout << (*it)->getUsername() << endl;
            }
        }
    }

    void showlikesdesc()
    {
        if (Likes.empty())
        {
            cout << "No likes yet" << endl;
        }
        else
        {
            cout << "No of Likes: " << no_of_likes << endl;
            cout << "Liked by: " << endl;
            for (list<User *>::reverse_iterator it = Likes.rbegin(); it != Likes.rend(); ++it)
            {
                cout << (*it)->getUsername() << endl;
            }
        }
    }

    void report_post(User *name)
    {
        int flag = 0;
        list<Post *>::iterator it = name->reports.begin();
        while (it != name->reports.end())
        {
            if ((*it)->PID == this->PID)
            {
                cout << "Post has already been reported by this user." << endl;
                flag = 1;
            }
            it++;
        }
        if (flag == 0)
        {
            this->reports++;
            name->reports.push_back(this);
            rep_users.push(name);
            if (reports >= REPORTS_MAX)
            {
                rep_posts.push(this);
            }
        }
    }

    void operator+(User *name)
    {
        if (no_of_likes < LIKE_MAX)
        {
            Likes.push_back(name);
            no_of_likes++;
        }
        else
        {
            cout << "Maximum number of likes reached." << endl;
        }
        update_tf();
    }

    void operator-(User *name)
    {
        int flag = 0;
        if (no_of_likes > 0)
        {
            for (list<User *>::iterator it = Likes.begin(); it != Likes.end(); it++)
            {
                if ((*it)->getUsername() == name->getUsername())
                {
                    Likes.remove(name);
                    no_of_likes--;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                cout << "User hasn't already liked this post" << endl;
            }
        }
        else
        {
            cout << "No likes to remove." << endl;
        }
        update_tf();
    }

    bool operator>(Post *p)
    {
        return ((this->tf) > (p->tf));
    }

    bool operator<(Post *p)
    {
        return ((this->tf) < (p->tf));
    }

    User *getAuthor()
    {
        return author;
    }

    void addComment(Comment *C)
    {
        CommentToInteger[C] = comment_ptr;
        IntegerToComment[comment_ptr] = C;
        comment_ptr++;
        Comments->addVertexComment();
    }

    void display();
    void EnterComment(User *, bool);
    void addEdgeComment(Comment *u, Comment *v, Post *p);
    void displayCommentSection(User *);
};

void review_post()
{
    if (rep_posts.empty())
    {
        cout << "No posts to review.\n";
        return;
    }
    Post *temp = rep_posts.front();
    int opt;
    while (true)
    {
        temp->display_post_details();
        cout << "Options available:" << endl
             << "1.Post is valid\n2.Post is invalid" << endl;
        cout << "Choose an option: ";
        cin >> opt;
        if (opt == 1)
        {
            temp->reports = 0;
            while (!(temp->rep_users.empty()))
            {
                temp->rep_users.pop();
            }
            cout << "Post has been found to be valid after evaluation" << endl
                 << endl;
            rep_posts.pop();
            return;
        }
        else if (opt == 2)
        {
            cout << "This post has been found to be violating our terms and conditions.Thus, this post will be deleted." << endl
                 << endl;
            vector<Post *>::iterator it = allPosts.begin();
            for (it; it != allPosts.end(); it++)
            {
                if ((*it)->PID == temp->PID)
                {
                    delete *it;
                    it = allPosts.erase(it);
                }
            }
            rep_posts.pop();
            return;
        }
        else
        {
            cout << "Invalid option" << endl
                 << endl;
            ;
        }
    }
}

/*
template <typename T>
class MM_Post:public Post{
    public:
        T *media;

        MM_Post(){
            Comments = new Graph();
            comment_ptr = 0;
            no_of_likes = no_of_shares = 0;
            reports = 0;
            time_of_creation = time(NULL);
            tf = 0;
            trending.insert(this);
            location = make_pair(0,0);
            setContent("");
            time_of_creation = time(NULL);
        }

        MM_Post(string content, User* author){
            Comments = new Graph();
            comment_ptr = 0;
            no_of_likes = no_of_shares = 0;
            reports = 0;
            this->author = author;
            setContent(content);
            time_of_creation = time(NULL);
            int time = time_of_creation;
            this->author->post_num++;
            this->PID = author->getUsername() + "_" + to_string(time) + "_" + to_string(this->author->post_num);
            tf = 0;
            trending.insert(this);
            graph.addPost(this->author->getUsername(), this->PID);
            location = make_pair(0,0);
        }

        MM_Post(string content, User* author, T* media){
            Comments = new Graph();
            comment_ptr = 0;
            no_of_likes = no_of_shares = 0;
            reports = 0;
            this->author = author;
            setContent(content);
            time_of_creation = time(NULL);
            int time = time_of_creation;
            this->author->post_num++;
            this->PID = author->getUsername() + "_" + to_string(time) + "_" + to_string(this->author->post_num);
            tf = 0;
            trending.insert(this);
            graph.addPost(this->author->getUsername(), this->PID);
            location = make_pair(0,0);
            this->media = media;
            cout<<"Post with media, created"<<endl;
        }

        MM_Post(string content, User* author, T* media, double latitude, double longitude){
            Comments = new Graph();
            comment_ptr = 0;
            no_of_likes = no_of_shares = 0;
            reports = 0;
            this->author = author;
            setContent(content);
            time_of_creation = time(NULL);
            int time = time_of_creation;
            this->author->post_num++;
            this->PID = author->getUsername() + "_" + to_string(time) + "_" + to_string(this->author->post_num);
            tf = 0;
            trending.insert(this);
            graph.addPost(this->author->getUsername(), this->PID);
            location = make_pair(latitude, longitude);
            allPosts.push_back(this);
            this->media = media;
            cout<<"Post with media, created"<<endl;
        }

        void display(){
            cout << "=====================Post======================="<<endl;
            cout << "By (" << author->getUsername()<<")" << endl;
            media->display();
            cout << this->getContent() << endl;
            cout << "================================================"<<endl;
        }

        template <typename U>
        void edit_post(U media){
            no_of_likes = no_of_shares = 0;
            string ncon;
            cout<<"Enter the Content for the edited post: ";
            cin.ignore();
            getline(cin,ncon);
            setContent(ncon);
            cout<<"Post has been modified with new media"<<endl;
            this->media = media;
        }

};
*/

/*
void User::create_MM_Post(){
    string con;
    double lat, lon;
    int ptype;
    string path;
    cout<<"Enter the content of the post: ";
    getline(cin,con);
    cout<<"Enter the location of the post: ";
    cin>>lat>>lon;
    cout<<"Multimedia Posts:\n1.Image Post\n2.Video Post\n"<<endl;
    cout<<"Select the type of media to post:";
    cin>>ptype;
    if (ptype == 1){
        cout<<"Enter the path of the image: ";
        cin>>path;
        Image* I = new Image(path);
        MM_Post<Image>* IP = new MM_Post<Image>(con,this,I, lat,lon);
    }else if (ptype == 2){
        cout<<"Enter the path of the video: ";
        cin>>path;
        Video* V = new Video(path);
        MM_Post<Video>(con,this,V, lat,lon);
    } else {
        cout<<"Invalid option selected\nError creating post\n"<<endl;
    }
    my_posts.push_back(pp);
}
*/

void addUser(User *u)
{

    mui[u->getUsername()] = num_users;
    miu[num_users] = u->getUsername();
    num_users++;
    global_users->addVertex();
}

class Edge
{
public:
    int u, v;
    double weight;
    Edge() {}
    Edge(int u, int v, double w)
    {
        // an edge between u and v is bidirected
        this->u = u;
        this->v = v;
        weight = w;
    }
    bool operator<(Edge e)
    {
        return this->weight < e.weight;
    }
    bool operator>(Edge e)
    {
        return this->weight > e.weight;
    }
    bool operator==(Edge e)
    {
        return this->weight == e.weight;
    }
    bool operator!=(Edge e)
    {
        return this->weight != e.weight;
    }
    bool operator<=(Edge e)
    {
        return this->weight <= e.weight;
    }
    bool operator>=(Edge e)
    {
        return this->weight >= e.weight;
    }
};

class UndirectedGraph
{
private:
    int edit_distance(string, string);
    int lcs(string, string);
    string preprocess(string);

public:
    vector<int> V;

    vector<vector<double>> distances;

    int nv;
    list<Edge> E;

    UndirectedGraph()
    {
        nv = 0;
    }
    void addVertex(User *u)
    {
        string uname = u->getUsername();
        muiUG[uname] = nv + 1;
        miuUG[nv + 1] = uname;
        addVertexUtil(nv);
    }

    void addVertex(Conversation *c)
    {
        micUGComm[nv] = c;
        mciUGComm[c] = nv;
        addVertexUtil(nv);
    }
    void addVertexUtil(int v)
    {
        nv++;
        V.push_back(v);
    }
    void addEdge(int u, int v, double w)
    {
        Edge e(u, v, w);
        E.push_back(e);
    }
    void addEdges();
    void updateWeight(string, string);
    void convWeights();
    void floydWarshall();
    void bellmanFordutil(vector<double> &, int);
    vector<double> bellmanFord(Conversation *);
    vector<Conversation *> suggestConvsBellmanFord(Conversation *);

    vector<double> dijkstrautil(int);
    list<pair<Conversation *, double>> dijkstra(Conversation *);
    vector<Conversation *> suggestConvs(Conversation *);
    vector<Conversation *> suggestConvsFloyd(Conversation *);
    void relax_vertices(int, vector<double> &, vector<bool>);
};

/*

some important global variables.

*/
UndirectedGraph Similarity_Graph;
UndirectedGraph Community_Graph;
vector<Graph *> ExplanationPost;
// list<Post *> allPosts; // not sure if used elsewhere
// this is changed to vector

// queue <Post*> rep_posts;
// vector<Post*> allPosts;
// post_Graph <string,string> allusers(USER_MAX);
// post_Graph <string,string> friends(FRIENDS_MAX);
// post_PostGraph graph;
// post_heap <Post*> trending;

class Message
{
public:
    User *author;
    time_t created_at;
    Message() { created_at = time(NULL); }
    virtual void display() = 0;
    virtual string getType() = 0;
    virtual User *getAuthor() = 0;
    virtual string getContent() { return ""; }; // often not needed in multimedia objects
    virtual void setContent(string) = 0;
    virtual void setAuthor(User *) = 0;
    virtual bool operator>(Message *msg)
    {
        return this->created_at > msg->created_at;
    }
    virtual bool operator<(Message *msg)
    {
        return this->created_at < msg->created_at;
    }
    virtual bool operator>=(Message *msg)
    {
        return this->created_at >= msg->created_at;
    }
    virtual bool operator<=(Message *msg)
    {
        return this->created_at <= msg->created_at;
    }
    virtual bool operator==(Message *msg)
    {
        return this->created_at == msg->created_at;
    }
    virtual bool operator!=(Message *msg)
    {
        return this->created_at != msg->created_at;
    }
};

class Multimedia : public Message
{
public:
    Multimedia(){};
    template <typename T>
    static bool validate(string path);
    void display() {};
    string getType() { return TEXT_MSG; }
    User *getAuthor() { return nullptr; }
    void setContent(string){};
    void setAuthor(User *) {};
    friend Message *prepare_message(User *);
    friend void calculate_time_passed(Message *);
    friend bool compare_fn(const Message *, const Message *);
};
class Video : public Multimedia
{
    string video_path;
    Audio *audio_for_video;
    const static int height = 300, width = 200;

public:
    int duration;
    Video()
    {
        duration = 0;
        video_path = "";
        cout << "Video created" << endl;
    }
    Video(string path)
    {
        video_path = path;
    }
    Video(int duration, string video_path)
    {
        this->duration = duration;
        this->video_path = video_path;
        cout << "Video created" << endl;
    }
    ~Video()
    {
        cout << "Video deleted" << endl;
    }
    bool isValidpath(string, string, User *);
    void display();
    User *getAuthor()
    {
        return author;
    }
    void setAuthor(User *author)
    {
        this->author = author;
    }
    string getType()
    {
        return VIDEO_MSG;
    }
};

class Notification
{
    double priority;
    time_t sent_at;

    void time_elapsed()
    {
        long t = sent_at;
        int diff = time(NULL) - t;
        cout << "(";
        if (diff > 60 && diff < 3600)
        {
            cout << diff / 60 << " minutes ago";
        }
        else if (diff > 60 && diff < 86400)
        {
            cout << diff / 3600 << " hours ago";
        }
        else if (diff > 60)
        {
            cout << diff / 86400 << " days ago";
        }
        else
        {
            cout << diff << " seconds ago";
        }
        cout << ")" << endl;
    }

public:
    string message;
    Conversation *belongs_to;
    Notification()
    {
        sent_at = time(NULL);
    }
    Notification(string message)
    {
        sent_at = time(NULL);
        this->message = message;
    }
    void setPriority(double priority)
    {
        this->priority = priority;
    }

    void setConversation(Conversation *conv)
    {
        this->belongs_to = conv;
    }

    void display()
    {
        cout << message;
        time_elapsed();
    }
    bool operator>(Notification n)
    {
        return this->priority > n.priority;
    }

    bool operator<(Notification n)
    {
        return this->priority < n.priority;
    }

    bool operator<=(Notification n)
    {
        return this->priority <= n.priority;
    }
    bool operator>=(Notification n)
    {
        return this->priority >= n.priority;
    }
};

class Story
{

    void calculate_time_passed();
    int calculate_num_views()
    {
        return viewers.size();
    }

public:
    int sid;
    Message *story_content;
    time_t time_of_creation;
    //   /  Comment *comments[MAX_C];
    int no_of_likes;
    vector<User> to_be_shared_with;
    User *author;
    set<User *> viewers;
    Story()
    {
        no_of_likes = 0;
        time_of_creation = time(NULL);
        // cout << "Story created" << endl;
    }
    Story(User *author)
    {
        no_of_likes = 0;
        time_of_creation = time(NULL);
        this->author = author;
        // cout << "Story created" << endl;
    }
    Story(const Story &s)
    {
        sid = s.sid;
        no_of_likes = s.no_of_likes;
        time_of_creation = s.time_of_creation;
        author = s.author;
        viewers = s.viewers;
        to_be_shared_with = s.to_be_shared_with;
        this->story_content = s.story_content;
        // s.viewers = viewers;
    }
    ~Story()
    {
        // cout << "Story deleted" << endl;
    }
    void create_story();
    void sendStory();
    void display();
    bool operator==(Story s)
    {
        if (s.author->getUsername() == author->getUsername())
        {
            if (s.sid == sid)
            {
                return true;
            }
        }
        return false;
    }
};
list<Story *> allstories;
class Image : public Multimedia
{
    string image_path;
    Audio *audio_for_image;
    const static int height = 300, width = 200;

public:
    Image()
    {
        image_path = "";
        // cout << "Image constructed" << endl;
    }
    Image(const string image_path)
    {
        this->image_path = image_path;
        //  cout << "Image constructed" << endl;
    }
    Image(User *author, const string path)
    {
        image_path = path;
        this->author = author;
    }
    ~Image()
    {
        //  cout << "Image deleted" << endl;
    }
    void display();
    User *getAuthor()
    {
        return author;
    }
    void setAuthor(User *author)
    {
        this->author = author;
    }
    string getType()
    {
        return IMAGE_MSG;
    }
};

class Audio : public Multimedia
{
    string audio_path;
    int duration, volume_level;

public:
    Audio()
    {
        duration = 0;
        volume_level = 50;
        cout << "Audio constructed" << endl;
    }
    Audio(string path)
    {
        audio_path = path;
    }
    Audio(string audio_path, int duration)
    {
        this->duration = duration;
        this->audio_path = audio_path;
        cout << "Audio constructed" << endl;
    }
    ~Audio()
    {
        cout << "Audio deleted" << endl;
    }
    void display();
    User *getAuthor()
    {
        return author;
    }
    void setAuthor(User *author)
    {
        this->author = author;
    }
    string getType()
    {
        return AUDIO_MSG;
    };
};

void User::create_post()
{
    string con;
    double lat, lon;
    int mp;
    int ptype;
    string path;
    cout << "Enter the content of the post: ";
    getline(cin >> ws, con);
    cout << "Enter the location of the post (space seperated latitude and longitude values): ";
    cin >> lat >> lon;
    cout << "Does your post contain multimedia(1:Yes,0:No):";
    cin >> mp;
    if (mp == 1)
    {
        cout << "Multimedia Posts:\n1.Image Post\n2.Video Post\n"
             << endl;
        cout << "Select the type of media to post:";
        cin >> ptype;
        if (ptype == 1)
        {
            cout << "Enter the path of the image: ";
            cin >> path;
            Image *I = new Image(path);
            Post *IP = new Post(con, this, lat, lon, I);
            my_posts.push_back(IP);
            allPosts.push_back(IP);
        }
        else if (ptype == 2)
        {
            cout << "Enter the path of the video: ";
            cin >> path;
            Video *V = new Video(path);
            Post *VP = new Post(con, this, lat, lon, V);
            my_posts.push_back(VP);
            allPosts.push_back(VP);
        }
        else
        {
            cout << "Invalid option selected\nError creating post\n"
                 << endl;
        }
    }
    else
    {
        Post *pp = new Post(con, this, lat, lon);
        my_posts.push_back(pp);
        allPosts.push_back(pp);
    }
}

void Post::display()
{
    cout << "=====================Post=======================" << endl;
    cout << "By (" << author->getUsername() << ")" << endl;
    if (this->ptype == 1)
    {
        post_image->display();
    }
    else if (this->ptype == 2)
    {
        post_video->display();
    }
    cout << content << endl;
    cout << "================================================" << endl;
}

class Conversation
{

protected:
    int count;
    int left_or_not[GROUP_MAX];
    User *creator;
    time_t creation_time;
    string community_name, group_name, community_description;

public:
    vector<User *> participants;
    AVLTree<Message *> chats_msgs; // array changed to list -now changed to a tree
    stack<Message *> history;
    double priority;

    // only history of chats deleted by the calling user shall be restored.
    int text_ptr;
    int p_ptr;
    // Story *chats_stories[MAX_C];
    //  Image *chats_images[MAX_C]; //depreciated
    //  Video *chats_videos[MAX_C]; //depreciated
    time_t story_t[MAX_C], image_t[MAX_C], video_t[MAX_C];

public:
    Conversation()
    {
        p_ptr = 0;
        creation_time = time(NULL);
    }
    virtual void add_participants(User *, User *) {};
    virtual void add_participants(int) {};
    virtual void create_interface() = 0;
    virtual void sendText(User *) {};
    virtual void sendMessage(Message *);
    virtual void createPoll() {};
    virtual void display_participants() = 0;
    virtual void joinGroup(User *) {};
    virtual char getType() = 0;
    virtual User *getCreator()
    {
        return nullptr;
    }

    virtual void setGroupName(string){};
    virtual void addPoll(Poll *) { return; }
    virtual string getGroupName() { return ""; };
    virtual void displayPolls() { return; }
    virtual ~Conversation(){};

    void restore_chat();
    void restore_message(Message *);
    void delete_message(Message *);
    virtual void acceptRequest(User *) {};
    virtual void issueRequest(User *) {};
    friend Conversation *search_dm_conversations(User, User);
    friend Conversation *search_dm_conversations(User *, User *);
    friend Conversation *search_dm_conversations(string user1, string user2);
    virtual void sendNotifications(string from);
    virtual string getCommunityName() { return community_name; }
    virtual string getCommunityDescription() { return community_description; }
    virtual void setCommunityName(string, string){};
    virtual void setCommunityDescription(string, string){};
    virtual void joinCommunity(User *) {}
    virtual void addMembers(User *) {}

    // operators
    bool operator<(Conversation *c)
    {
        return this->creation_time < c->creation_time;
    }

    bool operator>(Conversation *c)
    {
        return this->creation_time > c->creation_time;
    }

    bool operator>=(Conversation *c)
    {
        return this->creation_time >= c->creation_time;
    }

    bool operator<=(Conversation *c)
    {
        return this->creation_time <= c->creation_time;
    }
};

class DMConversation : public Conversation
{
    // inherits participants from the Conversation class
private:
    time_t last_seen[2];
    vector<Message *> starred_messages;

public:
    DMConversation()
    {
        priority = 2;
        count = 2;
        text_ptr = 0;
    }

    DMConversation(User *user1, User *user2)
    {
        priority = 2;
        count = 2;
        creator = user1;
        participants.push_back(user1);
        participants.push_back(user2);
    }

    ~DMConversation()
    {
        // arihato
    }
    // inherits the create_dm_interface and addParticipants

    void exitConvo(User *);
    void starMessage(Message *);
    char getType();

    template <class T>
    void sendText(User *);

    void create_interface();
    void display_participants();

    Conversation *search_node(SplayTree<Message *> T, string, string);
    void add_particpants(User *, User *);
};

class CommunityConversation : virtual public Conversation
{
protected:
    vector<User *> admins;
    int admin_ptr;
    string community_name;
    string community_description;
    Image *community_picture;

public:
    vector<Poll *> pollsForThisCommunity;
    CommunityConversation()
    {

        admin_ptr = 0;
        p_ptr = 0;
    }
    virtual ~CommunityConversation(){};

protected:
    bool authenticate(string username);

public:
    void setCommunityName(string, string);
    string getCommunityName();
    bool promoteToAdmin(string username);
    virtual void addMembers(string username, int count) = 0;
    virtual void addMembers(int) {};
    void setCommunityDescription(string username, string desc);
    string getCommunityDescription();
    void sendText(User *) {};
    char getType();
    virtual void addPoll(Poll *p)
    {
        pollsForThisCommunity.push_back(p);
    };
    virtual void createPoll();
    virtual void displayPolls();
    virtual User *getCreator()
    {
        return creator;
    }
    virtual void joinCommunity(User *) {};
    virtual void create_interface();
    virtual void display_participants();

    virtual void sendMessage(Message *msg);
    virtual void issueRequest(User *) {};
    virtual void acceptRequest(User *) {};
};
class RequestBasedCommunity : public CommunityConversation
{
private:
    queue<User *> request_queue;
    // User *request_queue[GROUP_MAX]; depreciated
    int request_ptr;

public:
    RequestBasedCommunity()
    {
        priority = 1.5;
        request_ptr = 0;
    }
    RequestBasedCommunity(User *creator)
    {
        priority = 1.5;
        request_ptr = 0;
        this->creator = creator;
        admins.push_back(creator);
        participants.push_back(creator);
        p_ptr++;
    }
    ~RequestBasedCommunity()
    {
        // arihato
    }
    void acceptRequest(User *); // admin and request queue
    void addMembers(string username, int count);
    void issueRequest(User *);
    // string getType();
};

class FreeJoinCommunity : public CommunityConversation
{
public:
    FreeJoinCommunity()
    {
        priority = 1;
    }
    FreeJoinCommunity(User *creator)
    {
        priority = 1;
        this->creator = creator;
        admins.push_back(creator);
        participants.push_back(creator);
        p_ptr++;
    }
    void addMembers(string, int) {};
    void addMembers(int);
    void joinCommunity(User *);
    // string getType();
};

class GroupConversation : public Conversation
{

private:
    Image *group_picture;
    string group_name;
    vector<User *> admins;
    int admin_ptr;

public:
    GroupConversation()
    {
        priority = 1.75;
        admin_ptr = 0;
        // group_name = "test_group";
        // cout << "Group constructed with the name " << group_name << endl;
    }

    GroupConversation(User *admin)
    {
        creator = admin;
        priority = 1.75;
        participants.push_back(creator);
    }

    // copy constructor
    GroupConversation(const GroupConversation &g)
    {
        priority = 1.75;
        admin_ptr = 0;
        this->group_name = g.group_name;
        this->creator = g.creator;
        admins.push_back(creator);
        for (int i = 0; i < g.count; i++)
        {
            participants.push_back(g.participants[i]);
        }

        // cout << "Group constructed with the name " << g.group_name << endl;
    }
    GroupConversation(User *creator, string group_name)
    {
        priority = 1.75;
        admin_ptr = 0;
        this->creator = creator;
        this->group_name = group_name;
        admins.push_back(creator);
        participants.push_back(creator);
        // cout << "Group constructed with the name " << group_name << endl;
    }
    GroupConversation(User *creator, User *users[GROUP_MAX], string group_name)
    {
        priority = 1.75;
        admin_ptr = 0;
        this->creator = creator;
        admins.push_back(creator);
        for (int i = 0; i < GROUP_MAX; i++)
        {
            participants.push_back(users[i]);
        }
        this->group_name = group_name;
        // cout << "Group constructed with the name " << group_name << endl;
    }
    ~GroupConversation()
    {
        // cout << "Group deleted" << endl;
    }

    void add_participants(int);
    string getGroupName();
    void joinGroup(User *);
    void addMembers(User *);
    void setGroupName(string gname);
    char getType();
    void sendMessage(Message *);
    void sendText(User *) {};
    void display_participants();
    void create_interface();
};

class String
{
    string content;

public:
    String(string content)
    {
        this->content = content;
    }
    String() { content = ""; }
    String(const String &other)
    {
        content = other.content;
    }
    void setContent(string);
    void display();
    string getContent();
};

class Emoji
{
    string content;
    string converted;
    string parse_and_replace(string);

public:
    Emoji()
    {
        content = "";
        converted = " ";
    }
    Emoji(string content) { this->content = converted = parse_and_replace(content); }
    Emoji(const Emoji &other)
    {
        content = other.content;
    }
    void display();
    void setContent(string);
    string getContent();
};

template <typename T = String>
class Text : public Message
{
    T content;
    User *author;

public:
    bool liked_or_not;
    time_t time_of_creation;
    User *replied_to;
    Text()
    {
        liked_or_not = false;
    }
    Text(string content)
    {
        this->content = T(content);
    }
    Text(User *author, string content)
    {
        this->author = author;
        this->content = T(content);
    }
    ~Text()
    {
        if (author)
        {
            // delete author;
        }
    }

    User *getAuthor();
    // T getContent(){};
    string getContent();
    void setContent(string);

    void setAuthor(User *);
    //  void setContent(T){};
    void display();
    string getType();
};

class Gif : public Image
{
private:
    string Gif_path;

public:
    Gif(const string path) : Gif_path(path) {}

    bool validate()
    {
        if (extractFormat(Gif_path) == "gif")
            return true;
        else
        {
            return false;
        }
    }
    void display()
    {
        cout << "From " << author->getUsername() << " ";
        calculate_time_passed(this);
        cout << "=============Gif==============" << endl;
        if (validate() == true)
        {

            cout << Gif_path << endl;
        }
        else
        {
            cout << "The provided gif doesn't match the format" << endl;
        }
        cout << "==============================" << endl;
    }
    string extractFormat(string format) { return "gif"; }
};

template <typename T>
class post_AVLNode
{
public:
    T data;
    int height;
    post_AVLNode *left;
    post_AVLNode *right;

    post_AVLNode(T val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class post_AVLTree
{
private:
    post_AVLNode<T> *root;

    int height(post_AVLNode<T> *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(post_AVLNode<T> *node)
    {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    post_AVLNode<T> *rotateRight(post_AVLNode<T> *y)
    {
        post_AVLNode<T> *x = y->left;
        post_AVLNode<T> *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    post_AVLNode<T> *rotateLeft(post_AVLNode<T> *x)
    {
        post_AVLNode<T> *y = x->right;
        post_AVLNode<T> *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    post_AVLNode<T> *insertNode(post_AVLNode<T> *node, T val)
    {
        if (node == nullptr)
            return new post_AVLNode<T>(val);

        if (val < node->data)
            node->left = insertNode(node->left, val);
        else if (val > node->data)
            node->right = insertNode(node->right, val);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        if (balance > 1 && val < node->left->data)
            return rotateRight(node);

        if (balance < -1 && val > node->right->data)
            return rotateLeft(node);

        if (balance > 1 && val > node->left->data)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && val < node->right->data)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    post_AVLNode<T> *minValueNode(post_AVLNode<T> *node)
    {
        post_AVLNode<T> *current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    post_AVLNode<T> *deleteNode(post_AVLNode<T> *root, T key)
    {
        if (root == nullptr)
            return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else
        {
            if (root->left == nullptr || root->right == nullptr)
            {
                post_AVLNode<T> *temp = root->left ? root->left : root->right;

                if (temp == nullptr)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;

                delete temp;
            }
            else
            {
                post_AVLNode<T> *temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = balanceFactor(root);

        if (balance > 1 && balanceFactor(root->left) >= 0)
            return rotateRight(root);

        if (balance > 1 && balanceFactor(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && balanceFactor(root->right) <= 0)
            return rotateLeft(root);

        if (balance < -1 && balanceFactor(root->right) > 0)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void levelOrderTraversalUtil(post_AVLNode<T> *root)
    {
        if (root == nullptr)
            return;

        queue<post_AVLNode<T> *> q;
        q.push(root);

        while (!q.empty())
        {
            post_AVLNode<T> *current = q.front();
            cout << current->data->PID << " ";
            q.pop();

            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
    }

public:
    post_AVLTree() : root(nullptr) {}

    void insert(T val)
    {
        root = insertNode(root, val);
    }

    void remove(T val)
    {
        root = deleteNode(root, val);
    }

    void levelOrderTraversal()
    {
        levelOrderTraversalUtil(root);
    }
};

void post_dijkstra(const string &sourceUser)
{
    map<string, int> distance;

    for (const auto &pair : allusers.adjLists)
    {
        distance[pair.first] = INT_MAX;
    }

    distance[sourceUser] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, sourceUser});

    while (!pq.empty())
    {
        string currUser = pq.top().second;
        int dist = pq.top().first;
        pq.pop();

        for (const auto &adjUser : allusers.adjLists[currUser])
        {
            if (dist + 1 < distance[adjUser])
            {
                distance[adjUser] = dist + 1;
                pq.push({distance[adjUser], adjUser});
            }
        }
    }

    cout << "Shortest paths from user " << sourceUser << ":\n";
    for (const auto &pair : distance)
    {
        if (pair.first == "None")
        {
            continue;
        }
        cout << "User: " << pair.first << ", Distance: ";
        if (pair.second == INT_MAX)
        {
            cout << "Infinity\n";
        }
        else
        {
            cout << pair.second << endl;
        }
    }
}

struct post_Edge
{
    Post *srcPost;
    Post *destPost;
    double weight;

    post_Edge(Post *src, Post *dest) : srcPost(src), destPost(dest)
    {
        weight = src->calculateDistance(*dest);
    }

    bool operator<(const post_Edge &other) const
    {
        return weight < other.weight;
    }
};

struct post_Edge1
{
    Post *srcPost;
    Post *destPost;
    double weight;

    post_Edge1(Post *src, Post *dest) : srcPost(src), destPost(dest)
    {
        weight = src->calculateDistance(*dest);
    }

    bool operator<(const post_Edge1 &other) const
    {
        return weight > other.weight;
    }
};

void post_findMinimumSpanningTree(const vector<Post *> &allPosts)
{
    priority_queue<post_Edge1> pq;
    set<Post *> visited;

    visited.insert(allPosts[0]);

    for (size_t i = 1; i < allPosts.size(); ++i)
    {
        pq.push(post_Edge1(allPosts[0], allPosts[i]));
    }

    while (!pq.empty() && visited.size() < allPosts.size())
    {
        post_Edge1 e = pq.top();
        pq.pop();

        if (visited.find(e.destPost) == visited.end())
        {
            visited.insert(e.destPost);
            cout << "post_Edge: " << e.srcPost->PID << " - " << e.destPost->PID << " Weight: " << e.weight << endl;
            for (size_t i = 0; i < allPosts.size(); ++i)
            {
                if (visited.find(allPosts[i]) == visited.end())
                {
                    pq.push(post_Edge1(e.destPost, allPosts[i]));
                }
            }
        }
    }
}

class post_DisjointSet
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    post_DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void merge(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV)
        {
            if (rank[rootU] > rank[rootV])
            {
                parent[rootV] = rootU;
            }
            else if (rank[rootU] < rank[rootV])
            {
                parent[rootU] = rootV;
            }
            else
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

void post_findMinimumSpanningTreeKruskal(const vector<Post *> &allPosts)
{
    vector<post_Edge> post_edges;

    for (size_t i = 0; i < allPosts.size(); ++i)
    {
        for (size_t j = i + 1; j < allPosts.size(); ++j)
        {
            post_edges.push_back(post_Edge(allPosts[i], allPosts[j]));
        }
    }

    sort(post_edges.begin(), post_edges.end());

    post_DisjointSet ds(allPosts.size());

    cout << "Minimum Spanning Tree post_Edges (Kruskal's Algorithm):\n";
    for (const auto &post_edge : post_edges)
    {
        int srcIndex = distance(allPosts.begin(), find(allPosts.begin(), allPosts.end(), post_edge.srcPost));
        int destIndex = distance(allPosts.begin(), find(allPosts.begin(), allPosts.end(), post_edge.destPost));

        if (ds.find(srcIndex) != ds.find(destIndex))
        {
            ds.merge(srcIndex, destIndex);
            cout << "post_Edge: " << post_edge.srcPost->PID << " - " << post_edge.destPost->PID << " Weight: " << post_edge.weight << endl;
        }
    }
}

void post_bellmanFord(const string &sourceUser)
{
    map<string, int> distance;

    // Initialize distances to all users as infinity
    for (const auto &pair : allusers.adjLists)
    {
        distance[pair.first] = INT_MAX;
    }

    // Distance to the source user is 0
    distance[sourceUser] = 0;

    // Relax edges repeatedly
    for (int i = 0; i < allusers.numVertices - 1; ++i)
    {
        for (const auto &pair : allusers.adjLists)
        {
            string currUser = pair.first;
            for (const auto &adjUser : allusers.adjLists[currUser])
            {
                // Update distance if shorter path found
                if (distance[currUser] != INT_MAX && distance[currUser] + 1 < distance[adjUser])
                {
                    distance[adjUser] = distance[currUser] + 1;
                }
            }
        }
    }

    // Check for negative cycles
    for (const auto &pair : allusers.adjLists)
    {
        string currUser = pair.first;
        for (const auto &adjUser : allusers.adjLists[currUser])
        {
            if (distance[currUser] != INT_MAX && distance[currUser] + 1 < distance[adjUser])
            {
                cout << "Graph contains negative cycle\n";
                return;
            }
        }
    }

    // Print shortest paths
    cout << "Shortest paths from user " << sourceUser << ":\n";
    for (const auto &pair : distance)
    {
        if (pair.first == "None")
        {
            continue;
        }
        cout << pair.first << ", Distance: ";
        if (pair.second == INT_MAX)
        {
            cout << "Infinity\n";
        }
        else
        {
            cout << pair.second << endl;
        }
    }
}

class Message_Post : public Post, public Message
{
public:
    double priority;
    User *author;
    int ptype;
    string content;
    Image *post_image;
    Video *post_video;
    Post *mpost;
    Message_Post(Post *post)
    {
        created_at = time(NULL);
        priority = 0.75;
        content = post->getContent();
        ptype = post->ptype;
        mpost = post;
        post_image = post->post_image;
        post_video = post->post_video;
        // author = post->getAuthor();
    }

    virtual User *getAuthor()
    {
        return this->author;
    }
    void setContent(string cont)
    {
        this->mpost->setContent(cont);
    }
    void setAuthor(User *name)
    {
        this->author = name;
    };
    string getType()
    {
        return POST_MSG;
    }

    void display()
    {
        // mpost->display();
        cout << "======================Post========================" << endl;
        cout << "Post by:" << author->getUsername() << endl;
        // mpost->media->display();
        cout << content << endl;
        cout << "==================================================" << endl;
        // mpost->interact_post();
    }
};

class Poll
{
private:
    string question;
    vector<string> options;
    vector<int> votes;
    string title;

public:
    Poll() {}
    Poll(const string &q) : question(q) {}

    void setQuestion(const string &q)
    {
        question = q;
    }

    void addOption(const string &option)
    {
        options.push_back(option);
        votes.push_back(0);
    }

    void display() const
    {
        cout << "Question: " << question << endl;
        for (size_t i = 0; i < options.size(); ++i)
        {
            cout << i + 1 << ". " << options[i] << endl;
        }
    }

    string getTitle()
    {
        return title;
    }

    void setTitle(string title)
    {
        this->title = title;
    }

    void vote(int index)
    {
        if (index > 0 && index <= static_cast<int>(options.size()))
        {
            votes[index - 1]++;
            cout << "Voted successfully!" << endl;
        }
        else
        {
            cout << "Invalid option index!" << endl;
        }
    }

    void showResults() const
    {
        cout << "Results:" << endl;
        for (size_t i = 0; i < options.size(); ++i)
        {
            cout << options[i] << ": " << votes[i] << " votes" << endl;
        }
    }
};
/*
void User::share_post(Post* P, User* receiver){
    friends.addEdge(this->getUsername(),receiver->getUsername());
    Conversation *c = search_node(this->getUsername(), receiver->getUsername());
    Message *pm = new Message_Post(P);
    pm->setAuthor(this);
    c->sendMessage(pm);
}

void User::share_post(Post* P, User* receiver1, User* receiver2){
    friends.addEdge(this->getUsername(),receiver1->getUsername());
    friends.addEdge(this->getUsername(),receiver2->getUsername());
    Message *pm = new Message_Post(P);
    pm->setAuthor(this);

    Conversation *c1 = search_node(this->getUsername(), receiver1->getUsername());
    c1->sendMessage(pm);

    Conversation *c2 = search_node(this->getUsername(), receiver2->getUsername());
    c2->sendMessage(pm);
}
*/

#endif

// int main(){}
