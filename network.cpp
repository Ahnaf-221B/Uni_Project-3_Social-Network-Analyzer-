#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

class User
{
public:
    string name;

    User(string n) : name(n) {}
};

class Graph
{
private:
    unordered_map<string, unordered_set<string>> adjList;

public:
    void addUser(string name);
    void addFriendship(string user1, string user2);
    vector<string> findMutualFriends(string user1, string user2);
    vector<string> suggestFriends(string user);
    void visualizeNetwork();
};

void Graph::addUser(string name)
{
    adjList[name];
}

void Graph::addFriendship(string user1, string user2)
{
    if (adjList.find(user1) == adjList.end() || adjList.find(user2) == adjList.end())
    {
        cout << "One or both users do not exist!" << endl;
        return;
    }
    adjList[user1].insert(user2);
    adjList[user2].insert(user1);
}

vector<string> Graph::findMutualFriends(string user1, string user2)
{
    vector<string> mutualFriends;
    if (adjList.find(user1) == adjList.end() || adjList.find(user2) == adjList.end())
    {
        cout << "One or both users do not exist!" << endl;
        return mutualFriends;
    }
    for (const auto &friend1 : adjList[user1])
    {
        if (adjList[user2].find(friend1) != adjList[user2].end())
        {
            mutualFriends.push_back(friend1);
        }
    }
    return mutualFriends;
}

vector<string> Graph::suggestFriends(string user)
{
    unordered_set<string> suggestions;
    if (adjList.find(user) == adjList.end())
    {
        cout << "User does not exist!" << endl;
        return vector<string>();
    }
    for (const auto &friend1 : adjList[user])
    {
        for (const auto &friend2 : adjList[friend1])
        {
            if (friend2 != user && adjList[user].find(friend2) == adjList[user].end())
            {
                suggestions.insert(friend2);
            }
        }
    }
    return vector<string>(suggestions.begin(), suggestions.end());
}

void Graph::visualizeNetwork()
{
    for (const auto &user : adjList)
    {
        cout << user.first << ": ";
        for (const auto &friend1 : user.second)
        {
            cout << friend1 << " ";
        }
        cout << endl;
    }
}

int main()
{
    Graph socialNetwork;
    int choice;
    string name, user1, user2;

    while (true)
    {
        cout << "Social Network Analysis" << endl;
        cout << "1. Add User" << endl;
        cout << "2. Add Friendship" << endl;
        cout << "3. Find Mutual Friends" << endl;
        cout << "4. Suggest Friends" << endl;
        cout << "5. Visualize Network" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            socialNetwork.addUser(name);
            break;
        case 2:
            cout << "Enter name of first user: ";
            cin.ignore();
            getline(cin, user1);
            cout << "Enter name of second user: ";
            getline(cin, user2);
            socialNetwork.addFriendship(user1, user2);
            break;
        case 3:
            cout << "Enter name of first user: ";
            cin.ignore();
            getline(cin, user1);
            cout << "Enter name of second user: ";
            getline(cin, user2);
            {
                vector<string> mutualFriends = socialNetwork.findMutualFriends(user1, user2);
                if (mutualFriends.empty())
                {
                    cout << "No mutual friends found or one of the users does not exist!" << endl;
                }
                else
                {
                    cout << "Mutual Friends: ";
                    for (const auto &friend1 : mutualFriends)
                    {
                        cout << friend1 << " ";
                    }
                    cout << endl;
                }
            }
            break;
        case 4:
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            {
                vector<string> suggestions = socialNetwork.suggestFriends(name);
                if (suggestions.empty())
                {
                    cout << "No suggestions available or user does not exist!" << endl;
                }
                else
                {
                    cout << "Suggested Friends: ";
                    for (const auto &suggestion : suggestions)
                    {
                        cout << suggestion << " ";
                    }
                    cout << endl;
                }
            }
            break;
        case 5:
            socialNetwork.visualizeNetwork();
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}
