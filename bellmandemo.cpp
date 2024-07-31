#include "headers.hpp"

int main(){
    User *u1 = new User("naren", "naren3", "naren@gmail.com");
    User *u2 = new User("jan", "jan3", "jan@gmail.com");
    User *u3 = new User("jan3", "jan3", "jan@gmail.com");
    User *u4 = new User("nar1", "naren3", "nar1@gmail.com");
    User *u5 = new User("nar2", "nar2@gmail.com", "naren3");
    User *u6 = new User("nar3", "nar3@gmail.com", "naren3");
    User *u7 = new User("nar4", "nar4@gmail.com", "naren3");

    User *us[] = {u1, u2, u3, u4, u5, u6, u7};

    for (int i = 0; i < 6; i++)
    {
        store_user(us[i]);
        Similarity_Graph.addVertex(us[i]);
    }

    CommunityConversation *conv1 = new FreeJoinCommunity(u5);
    CommunityConversation *conv2 = new FreeJoinCommunity(u2);
    CommunityConversation *conv3 = new FreeJoinCommunity(u3);
    CommunityConversation *conv4 = new FreeJoinCommunity(u4);
    CommunityConversation *conv5 = new FreeJoinCommunity(u1);
    Conversation *conv6 = new DMConversation(u5, u6);

    conv1->setCommunityName(u5->getUsername(), "Birds");
    conv2->setCommunityName(u2->getUsername(), "Animals");
    conv3->setCommunityName(u3->getUsername(), "New York");
    conv4->setCommunityName(u4->getUsername(), "London");
    conv5->setCommunityName(u1->getUsername(), "Berlin");

    conv1->setCommunityDescription(u5->getUsername(), "This is about the beautiful avain species.. birds .");
    conv2->setCommunityDescription(u2->getUsername(), "This is about those that roam in the wild .. beautiful species and creations .. ");
    conv4->setCommunityDescription(u4->getUsername(), "This is about the beautiful capital city , London in the united kingdom of europe ");
    conv5->setCommunityDescription(u1->getUsername(), "This is about the magnificent capital city of germany , berlin. ");
    conv3->setCommunityDescription(u3->getUsername(), "This is about the capital city of United states of america . The technical marvel ");


    Conversation *convs[] = {conv1, conv2, conv3, conv4, conv5, conv6};
    for (Conversation *c : convs)
    {
        store_conv(c);
        Community_Graph.addVertex(c);
    }

    Community_Graph.convWeights();

    string description;
    cout << "Describe what u expect (include keywords for better suggestions) "<<endl; 
    getline(std::cin , description, '\n');
    CommunityConversation *tempconv = new FreeJoinCommunity(u2);
    tempconv->setCommunityDescription(u2->getUsername(), description);

    vector<Conversation*> suggestions = Community_Graph.suggestConvsBellmanFord(tempconv);

    cout << "We suggest you to join the following communities" <<endl;

    for(int i = 0; i < suggestions.size(); i++){
        cout << i+1 << " . "<< suggestions[i]->getCommunityName() << endl;
    }

    return 0;

}