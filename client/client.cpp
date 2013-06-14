/*========================================================================================================================================
@GUSTAVO TEIXEIRA GOMES

*Client TCP

* To-do:
* - improve error checking
========================================================================================================================================*/

#include "..\socket\socket.h"
#include <fstream>

#define _DEBUG_ 0

using namespace std;

int main() {

  try {
	// Define variables
	ifstream inputFile;
	ofstream outputFile;
	char *inputBuffer;
	string outputBuffer;
	char *inputFileName = "../grip-client/worldData.txt";
	char *outputFileName = "../grip-client/command.txt";
		
	// Connect to the sever
    SocketInterface::SocketClient server(SERVER_IP, SERVER_PORT);
	
	// Open and Send file
	inputFile.open(inputFileName, std::ifstream::binary);
	if (inputFile.is_open()) {
		// Transfering the file worldData
		cout << "Transfering the file" << endl;
		while(inputFile.good()) {
			inputBuffer = new char [MAXBUFFER];
			inputFile.read(inputBuffer, MAXBUFFER);
			if (_DEBUG_) {
				cout << "Count: " << inputFile.gcount() << endl;
				cout << inputBuffer << endl;
			}
			server.SendBytes(inputBuffer, (int)inputFile.gcount());
			delete[] inputBuffer;
		}
		inputFile.close();
		cout << "Ending Transfering the file" << endl;
		
		cout << "Receiving the file" << endl;
		// Receiving the file command
		outputFile.open(outputFileName, std::ofstream::binary);
		bool stillConnected = true;
		while (1) {
			outputBuffer = server.ReceiveBytes();
			if (_DEBUG_) cout << "Buffer: " << outputBuffer.size() << endl;
			if (outputBuffer.empty()) {
				break;
			}
			outputFile << outputBuffer;
			outputFile.flush();
			if (outputBuffer.size() < MAXBUFFER) {
				break;
			}
		}
		outputFile.flush();
		outputFile.close();
		cout << "Ending Receiving the file" << endl;
	}
	else {
		cout << "Openning " << inputFileName << " file error" << endl;
	}
  }
  catch (const char* s) {
    cerr << s << endl;
	if (_DEBUG_) system("pause");
  } 
  catch (std::string s) {
    cerr << s << endl;
	if (_DEBUG_) system("pause");
  } 
  catch (...) {
    cerr << "unhandled exception\n";
	if (_DEBUG_) system("pause");
  }
  if (_DEBUG_) {
	  system("pause");
	  system("comp ..\\grip-client\\worldData.txt ..\\icarus-server\\worldData.txt /A");
	  system("comp ..\\grip-client\\command.txt ..\\icarus-server\\command.txt /A");
  }
  return 0;
}