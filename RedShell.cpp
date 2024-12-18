////////// INIT ////////////////////////////////////////////////////////////////////////////////////
#include "RedShell.hpp"

///// Globals /////////////////////////////////////////////////////////////
pid_t procNum = 0; // Process Number 



////////// SIGNALS /////////////////////////////////////////////////////////////////////////////////

void shutdown_handler( int signum ) {
    // Catch SIGINT
    
    cout << endl << "MicroShell (" << getpid() << "): Interrupt signal (" << signum << ") received." << endl
         << "It's treason, then." << endl;

    exit( signum );  
}



////////// HELPER FUNCTIONS ////////////////////////////////////////////////////////////////////////

vector<string> list_path( string path ){
    // List all the files in a directory
    // https://stackoverflow.com/a/37494654
    vector<string> rtnVec;
    for( const auto& entry : fs::directory_iterator( path ) ){  rtnVec.push_back( entry.path().string() );  }
    return rtnVec;
}

vector<string> split( string s , char sep ){
    vector<string> rtnVec;
    string currWord; // ------------- Current word between separators
    s.append( string( 1 , sep ) ); // Delimiter termination hack
    int len = s.length(); // -------- Length of input string
    // For each char in the string
    for( int i = 0 ; i < len ; i++ ){
        if( s[i] != sep ){ // If not separator, accumulate char to `currWord`
            currWord += s[i];
        }else{ // else is separator, 
            // add word if we accumulated one
            if( currWord.length() > 0 ){  rtnVec.push_back( currWord );  } // Assign word to array
            currWord = "";
        }
    }
    return rtnVec;
}


bool has_substr( string& superStr , string& subStr ){
    // Return true if `superStr` containst `subStr`, otherwise return false
    std::size_t found = superStr.find( subStr );
    return found != string::npos;
}


vector<string> get_avail_cmd( string path = "./out" , string prefix = "u_" ){
    // Return the available commands: 
    // Which are programs in `path` whose filenames begin with `prefix` 
    vector<string> progList = list_path( path );
    size_t len = progList.size();
    vector<string> temp;
    vector<string> cmdList;
    string elem;
    for( size_t i = 0 ; i < len ; i++ ){
        temp = split( progList[i] , '/' );
        elem = temp[ temp.size() - 1 ];
        if( has_substr( elem , prefix ) ){  cmdList.push_back( elem );  }
    }
    return cmdList;
}

vector<string> parse( string prefix ){
    // Parse user input, Return a vector of strings, Empty vector indicates exit condition
    
    // 0. Init and clear any lingering errors in the `cin` buffer
    string userInput;
    vector<string> rtnVec;
    vector<string> errVec;
    vector<string> cmdLst = get_avail_cmd();  cmdLst.push_back( "exit" );

    if( cin.fail() ){
        cin.clear(); // --------- Ignore all errors
        cin.ignore( INT_MAX ); // Completely discard `cin` buffer
    }

    // 0.1. List available commands and show the shell prompt
    cout << endl << "Available Commands: " << cmdLst << endl << "u-shell$ ";;

    // 1. Take input, If no error then ...
    if( getline( cin , userInput ) ){
        if( userInput.length() == 0 )  return errVec;

        // 2. Split the input and search for the program
        rtnVec = split( userInput , ' ' );
        string path = prefix + rtnVec[0];
        
        // 3. Check for exit command
        if( userInput == "exit" ){
            cout << endl << "EXIT shell!" << endl;
            return errVec;
        }
        
        // 4. Check that the program exists
        if( is_arg_in_vector( rtnVec[0] , cmdLst ) ){
            rtnVec[0] = path;
            return rtnVec;
        } else  return errVec;
    // 5. else error in parsing, return the exit vector
    } else  return errVec;
}



////////// MAIN ////////////////////////////////////////////////////////////////////////////////////

int main( int argc, char *argv[] ){
    
    ///// Register signal handlers /////
    signal( SIGINT , shutdown_handler );

    ///// Init /////
    bool /*-----*/ running    = 1;
    string /*---*/ pathPrefix = "./out/";
    vector<string> input;
    // char* /*----*/ cPath;
    // char* /*----*/ childArgs[128];
    size_t /*---*/ N_args = 0;
    pid_t /*----*/ myID   = getpid();

    cout << "Started MicroShell as PID " << myID << ", part of " << getpgid( myID ) << " process group" << endl;

    // FIXME, START HERE: REPL

}