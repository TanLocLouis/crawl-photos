#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

const string findPattern = "<img src=\"https://voz.vn/attachment"; // pattern to dectect data

void input(string& url, int& startPage, int& endPage) {
    cout << "Link: ";
    cin >> url;
    cout << "Start from page: ";
    cin >> startPage;
    cout << "To: ";
    cin >> endPage;
}

void trimUrl(string& url) {
    size_t pos = url.find_last_of("/");
    url = url.substr(0, pos + 1);
    cout << "Debug" << endl;
    cout << url << endl;
}

void commit() {
        fstream f1("VOZ.txt");
    
        string text = "";
        string img = "";
        while (getline(f1, text)){// get data current page
	    int countQuote = 0;
	    int start = 0;
            if (text.find(findPattern) != string::npos) {
                for (int i = 0; i < text.length(); i++) {
                    if (text[i] == '"') {
			countQuote++;
			cout << countQuote << endl;
			if (countQuote == 1) start = i;
			if (countQuote == 2) {
			        img = text.substr(start, i - start + 1);
				cout << "Debug:";
				cout << img << endl; cout << endl;
			        system(("wget --user-agent=\"Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0\" " + img + " -O Photo_" + to_string(rand()) + ".jpg").c_str()); // download data
			        cout << img << endl; // show link of data
			        cout << "------------------------------------------------------------------" << endl;
			        cout << endl;
				break;
			}
                    }             
                }
            }
        }
        f1.close();
}

void get_data(const string& url, const int& startPage, const int& endPage) {
        for (int each_page = startPage; each_page <= endPage; each_page++) { // get data each page
            system(("wget -O VOZ.txt --user-agent=\"Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0\" " + url + "page-" + to_string(each_page)).c_str()); //download current page
            commit();
        }
}

int main() {
    srand(time(0));

    string url = "";
    int startPage = 0;
    int endPage = 0;
    input(url, startPage, endPage);
    trimUrl(url);

    get_data(url, startPage, endPage);
}
