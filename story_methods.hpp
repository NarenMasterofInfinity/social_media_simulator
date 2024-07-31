#include "classes.hpp"
#include "user_methods.hpp"
#include "multimedia_methods.hpp"
#include "text_methods.hpp"
#include "str_emoji_methods.hpp"
#include "graph.hpp"
#include "user_db.hpp"

#ifndef STORY_H
#define STORY_H

void Story::create_story()
{
    int ch;
    string path1;
    string content1;
    //  Message *element;
    bool created_story = false;

    do
    {
        cout << "1. Audio\n2. Video\n3. Image\n4. Normal Text\n5. Emojified Text\n6. Exit" << endl;
        cout << "Enter the choice of your story: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
        {
            cout << "Enter Audio path: ";
            getline(cin >> ws, path1);
            story_content = new Audio(path1);
            created_story = true;
        }
        break;
        case 2:
        {
            cout << "Enter Video path: ";
            getline(cin >> ws, path1);
            story_content = new Video(path1);
            created_story = true;
        }
        break;
        case 3:
        {
            cout << "Enter Image path: ";
            getline(cin >> ws, path1);
            story_content = new Image(path1);
            created_story = true;
        }
        break;
        case 4:
        {
            cout << "Enter Text content: ";
            getline(cin >> ws, content1);
            story_content = new Text<String>(content1);
            created_story = true;
        }
        break;
        case 5:
        {
            cout << "Enter Text content: ";
            getline(cin >> ws, content1);
            story_content = new Text<Emoji>(content1);
            created_story = true;
        }
        break;
        case 6:
        {
            cout << "Exiting.." << endl;
        }
        break;
        default:
        {
            cout << "Invalid option. Please try again." << endl;
        }
        break;
        }
    } while (ch < 1 || ch > 6);

    if (created_story)
    {
        story_content->setAuthor(author);
        // story_content = element;

        // Story *putin = this;
        author->my_stories.push_back(*this);
        this->sendStory();
    }
    else
    {
        cout << "No story created." << endl;
    }
}

void Story::calculate_time_passed()
{
    long t = time_of_creation;
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

void Story ::display()
{
    cout << "=======================Story========================" << endl;
    // if (nullptr != author)
    // {
    //     cout << author->getUsername() << endl;
    // }
    // calculate_time_passed();
    story_content->display();
    cout << "Number of likes : " << no_of_likes << endl;
    cout << "====================================================" << endl;
}

void Story::sendStory()
{
    vector<User> friends = findfriends(author);
    to_be_shared_with.push_back(*author);
    for (User u : friends)
    {

        to_be_shared_with.push_back(u);

        User usr = User::search_user_no_pointer(u.getUsername());
        (usr.my_stories).push_back(*this);

        update_user(usr);
    }
    sid = allstories.size()+1;
    allstories.push_back(this);
    cout << "Story successfully created!" << endl;
    this->display();

}

#endif