#include "classes.hpp"

#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H
void Image::display()
{
    if (nullptr != author)
    {
        cout << "From " << author->getUsername() << " ";
        calculate_time_passed(this);
    }
    cout << "============Image=============" << endl;
    cout << endl;
    string command = "tiv -h 20 -w 20 " + image_path;
    const char *command_to_execute = command.c_str();
    int ret = system(command_to_execute);
    cout << endl;
    if (ret != 0)
    {
        cout << "Path: " << image_path << endl;
    }
    cout << "==============================" << endl;
}
void Video::display()
{
    cout << "From " << author->getUsername() << " ";
    calculate_time_passed(this);
    cout << "============Video=============" << endl;
    cout << video_path << endl;
    cout << "==============================" << endl;
}

void Audio::display()
{
    cout << "From " << author->getUsername() << " ";
    calculate_time_passed(this);
    cout << "============Audio=============" << endl;
    cout << audio_path << endl;
    cout << "==============================" << endl;
}
template <typename T>
bool Multimedia::validate(string path)
{
    cout << "This object is not supported yet!" << endl;
    return 0;
}

template <>
bool Multimedia::validate<Image>(string path)
{
    unsigned int location = path.find('.');
    location++;
    string extension = path.substr(location);
    vector<string> possible_extensions = {"jpg", "jpeg", "png"};
    for (auto i = possible_extensions.begin(); i != possible_extensions.end(); i++)
    {
        if (*i == extension)
        {
            return 1;
        }
    }
    cout << "Unsupported Image format!" << endl;
    return 0;
}
template <>
bool Multimedia::validate<Video>(string path)
{
    unsigned int location = path.find('.');
    location++;
    string extension = path.substr(location);
    vector<string> possible_extensions = {"mp4", "mkv", "mpe4"};
    for (auto i = possible_extensions.begin(); i != possible_extensions.end(); i++)
    {
        if (*i == extension)
        {
            return 1;
        }
    }
    cout << "Unsupported Video format!" << endl;
    return 0;
}
template <>
bool Multimedia::validate<Audio>(string path)
{
    unsigned int location = path.find('.');
    location++;
    string extension = path.substr(location);
    vector<string> possible_extensions = {"wav", "aav", "mp3"};
    for (auto i = possible_extensions.begin(); i != possible_extensions.end(); i++)
    {
        if (*i == extension)
        {
            return 1;
        }
    }
    cout << "Unsupported Audio format!" << endl;
    return 0;
}
string getPathType(string path)
{
    return IMAGE_MSG;
}

Message *prepare_message(User *owner)
{
    cout << "Preparing message for " << owner->getUsername() << endl;
    cout << "What type of message do you wish to send? " << endl;
    cout << "    1.Normal text" << endl;
    cout << "    2.Emojified text" << endl;
    cout << "    3.Image" << endl;
    cout << "    4.Audio" << endl;
    cout << "    5.Video" << endl;
    cout << "    6.Gif" << endl;
    int choice;
    cout << "Your choice : ";
    cin >> choice;
    Message *data;
    string content, path;
    switch (choice)
    {
    case 1:
        cout << "Enter text: ";
        getline(cin >> ws, content);
        data = new Text<String>(content);
        break;
    case 2:

        cout << "Enter text: ";
        getline(cin >> ws, content);
        data = new Text<Emoji>(content);
        break;
    case 3:

        cout << "Enter path: ";
        getline(cin >> ws, path);
        data = new Image(path);
        break;
    case 4:

        cout << "Enter path: ";
        getline(cin >> ws, path);
        data = new Audio(path);
        break;
    case 5:

        cout << "Enter path: ";
        getline(cin >> ws, path);
        data = new Video(path);
        break;
    case 6:

        cout << "Enter path: ";
        getline(cin >> ws, path);
        data = new Gif(path);
        break;
    default:
        cout << "Invalid choice!" << endl;
        break;
    }
    cout << "================================" << endl;
    data->setAuthor(owner);
    return data;
}

void calculate_time_passed(Message *msg)
{
    long t = msg->created_at;
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

#endif