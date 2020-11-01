t<<"connected  "<<new_socket<<endl;
lient[n].ip=inet_ntoa(address.sin_addr);
//cout<<"1\n";
strcpy( client[n].IP , (client[n].ip).c_str());
//cout<<"2\n";
client[n].portNo=(int) ntohs(address.sin_port);
//client[n].portNo=;//(int) ntohs(address.sin_port);
cout<<"3\n";
client[n].soc