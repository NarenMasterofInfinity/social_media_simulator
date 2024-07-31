#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Poll {
private:
    string question;
    vector<string> options;
    vector<int> votes;
    string title;

public:
    Poll() {}
    Poll(const string &q) : question(q) {}

    void setQuestion(const string &q) {
        question = q;
    }

    void addOption(const string &option) {
        options.push_back(option);
        votes.push_back(0);
    }

    void display() const {
        cout << "Question: " << question << endl;
        for (size_t i = 0; i < options.size(); ++i) {
            cout << i + 1 << ". " << options[i] << endl;
        }
    }

   string getTitle(){
        return title;
    }

    void setTitle(string title){
        this->title = title;
    }


    void vote(int index) {
        if (index > 0 && index <= static_cast<int>(options.size())) {
            votes[index - 1]++;
            cout << "Voted successfully!" << endl;
        } else {
            cout << "Invalid option index!" << endl;
        }
    }

    void showResults() const {
        cout << "Results:" << endl;
        for (size_t i = 0; i < options.size(); ++i) {
            cout << options[i] << ": " << votes[i] << " votes" << endl;
        }
    }
};

void create_poll(Poll &poll, const string &question, const vector<string> &options) {
    poll.setQuestion(question);
    for (const string &option : options) {
        poll.addOption(option);
    }
}

void display_poll(const Poll &poll) {
    poll.display();
}

void vote_poll(Poll &poll) {
    int choice;
    cout << "Enter the number of your choice: ";
    cin >> choice;
    cin.ignore(); 
    poll.vote(choice);
}

void result_poll(const Poll &poll) {
    poll.showResults();
}

int main() {
    Poll poll;
    create_poll(poll, "What's your favourite colour?", {"Red", "Blue", "Green", "Yellow"});
    
    display_poll(poll);

    char voting;
    // done to cast multiple votes da 
    do {
        vote_poll(poll);
        cout << "Do you want to vote again? (y/n): ";
        cin >> voting;
        cin.ignore(); 
    } while (voting == 'y' || voting == 'Y');
	// add user thingy here
    result_poll(poll);

    return 0;
}