/*========================================================================================================================================
@GUSTAVO TEIXEIRA GOMES

*Server TCP
========================================================================================================================================*/

#include "..\socket\socket.h"
#include <fstream>
#include <process.h>

#define _DEBUG_ 0

using namespace std;

int main(int argc, char *argv[])
{
	// Define variables
	ifstream inputFile;
	ofstream outputFile;
	char *inputBuffer;
	string outputBuffer;
	char *outputFileName = "../icarus-server/worldData.txt";
	char *inputFileName = "../icarus-server/command.txt";
			
  	// Create socket
	SocketInterface::SocketServer in(SERVER_PORT,5, SocketInterface::NonBlockingSocket);

	while (1) {
	cout << "Waiting on port " << SERVER_PORT << endl;
	
	// Wait for the client
	int connectionResult = WSAEWOULDBLOCK;
	SocketInterface::Socket* client;
	while(connectionResult==WSAEWOULDBLOCK)
	{
		//std::cout<<"Waiting for incoming connections...\r\n";
		client = in.Accept();
		connectionResult=WSAGetLastError();
	}
	//system("pause");
	//SocketInterface::Socket* client = in.Accept();
	
	// Receiving the file worldData
	cout << "Receiving the file" << endl;
	outputFile.open(outputFileName, std::ofstream::binary);
	while (1) {
		outputBuffer = client->ReceiveBytes();
		if (_DEBUG_) cout << "Buffer: " << outputBuffer.size() << endl;
		int nError=WSAGetLastError();
		if(nError!=WSAEWOULDBLOCK&&nError!=0)
		{
			cout<<"Winsock error code: "<<nError<<"\r\n";
			cout<<"Server disconnected!\r\n";
			// Close our socket entirely
			client->Close();

			break;
		}
		else if (nError==WSAEWOULDBLOCK) {
			// Do nothing
			cout << "WSAEWOULDBLOCK" << endl;
		}
		else {
			if (outputBuffer.empty()) {
				break;
			}
			outputFile << outputBuffer;
			if (outputBuffer.size() < MAXBUFFER) {
				break;
			}
		}
	}
	outputFile.flush();
	outputFile.close();
	cout << "Ending Receiving the file" << endl;
		
	cout << "Transfering the file" << endl;
	// Open and Send file command
	inputFile.open(inputFileName, std::ifstream::binary);
	if (inputFile.is_open()) {
		while(inputFile.good()) {
			inputBuffer = new char [MAXBUFFER];
			inputFile.read(inputBuffer, MAXBUFFER);
			if (_DEBUG_) {
				cout << "Count: " << inputFile.gcount() << endl;
				cout << inputBuffer << endl;
			}
			client->SendBytes(inputBuffer, (int)inputFile.gcount());
			delete[] inputBuffer;
		}
		inputFile.close();
		cout.flush();
		cout << "Ending Transfering the file" << endl;
	}
	else {
		cout << "Openning " << inputFileName << " file error" << endl;
	}
	delete[] client;
  }
 
  return 0;
}
