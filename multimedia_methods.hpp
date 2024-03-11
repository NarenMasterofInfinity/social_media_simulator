#include "classes.hpp"

void Image::display(){
    cout<<"From "<<author->getUsername()<<endl;
    cout<<"============Image============="<<endl;
    cout<<image_path<<endl;
    cout<<"=============================="<<endl;
}
void Video::display(){
    cout<<"From "<<author->getUsername()<<endl;
    cout<<"============Video============="<<endl;
    cout<<video_path<<endl;
    cout<<"=============================="<<endl;
}

void Audio::display(){
    cout<<"From "<<author->getUsername()<<endl;
    cout<<"============Audio============="<<endl;
    cout<<audio_path<<endl;
    cout<<"=============================="<<endl;
}
template<typename T>
bool Multimedia::validate(string path){
    cout<<"This object is not supported yet!"<<endl;
    return 0;
}

template<> bool Multimedia::validate<Image>(string path){
    unsigned int location = path.find('.');
    location++;
    string extension = path.substr(location);
    vector<string> possible_extensions = {"jpg", "jpeg", "png"};
    for(auto i = possible_extensions.begin(); i!=possible_extensions.end();i++){
        if(*i == extension){
            return 1;
        }
    }
    cout<<"Unsupported Image format!"<<endl;
    return 0;
}
template<> bool Multimedia::validate<Video>(string path){
    unsigned int location = path.find('.');
    location++;
    string extension = path.substr(location);
    vector<string> possible_extensions = {"mp4", "mkv", "mpe4"};
    for(auto i = possible_extensions.begin(); i!=possible_extensions.end();i++){
        if(*i == extension){
            return 1;
        }
    }
    cout<<"Unsupported Video format!"<<endl;
    return 0;
}
template<> bool Multimedia::validate<Audio>(string path){
    unsigned int location = path.find('.');
    location++;
    string extension = path.substr(location);
    vector<string> possible_extensions = {"wav", "aav", "mp3"};
    for(auto i = possible_extensions.begin(); i!=possible_extensions.end();i++){
        if(*i == extension){
            return 1;
        }
    }
    cout<<"Unsupported Audio format!"<<endl;
    return 0;
}
string getPathType(string path){
    return IMAGE_MSG;
}