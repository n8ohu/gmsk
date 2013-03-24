//////////////////////
// API version of the GMSK modem for 10m / VHF / UHF communication
// using codec2
// version 0 (versionid 0x27f301): 4800 bps, 1/3 repetition code FEC


/*
 *      Copyright (C) 2013 by Kristoff Bonne, ON1ARF
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; version 2 of the License.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 */


// Release information
// version 20130310 initial release


// c2gmsk API  numeric messages: 0 up to 4 return values

// functions:
// int queue_m_msg_0;
// int queue_m_msg_1;
// int queue_m_msg_2;
// int queue_m_msg_3;
// int queue_m_msg_4;
// int queue_m_nodataifempty

////////////// MOD CHAIN

// queue MESSAGES: no additional data
int queue_m_msg_0 (session * sessid, int message) {
c2gmsk_msg_0 msg;
int ret;

// sanity checks
ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

msg.tod=message;
msg.datasize=0; // no data

ret=c2gmskchain_add(sessid->m_chain,&msg,sizeof(msg));

return(ret);
}; // end function

// queue MESSAGES: 1 datafield to send
int queue_m_msg_1 (session * sessid, int message, int data0) {
c2gmsk_msg_1 msg;
int ret;

// sanity checks
ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

msg.tod=message;
msg.datasize=sizeof(int); // 1 integer
msg.data0=data0;

ret=c2gmskchain_add(sessid->m_chain,&msg,sizeof(msg));

return(ret);
}; // end function

// queue MESSAGES: 2 datafield to send
int queue_m_msg_2 (session * sessid, int message, int data0, int data1) {
c2gmsk_msg_2 msg;
int ret;

// sanity checks
ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

msg.tod=message;
msg.datasize=(sizeof(int)<<1); // 2 integers
msg.data0=data0;
msg.data1=data1;

ret=c2gmskchain_add(sessid->m_chain,&msg,sizeof(msg));

return(ret);
}; // end function

// queue MESSAGES: 3 datafield to send
int queue_m_msg_3 (session * sessid, int message, int data0, int data1, int data2) {
c2gmsk_msg_3 msg;
int ret;

// sanity checks
ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

msg.tod=message;
msg.datasize=sizeof(int) + sizeof(int) + sizeof(int); // 3 integers
msg.data0=data0;
msg.data1=data1;
msg.data2=data2;

ret=c2gmskchain_add(sessid->m_chain,&msg,sizeof(msg));

return(ret);
}; // end function

// queue MESSAGES: 4 datafield to send
int queue_m_msg_4 (session * sessid, int message, int data0, int data1, int data2, int data3) {
c2gmsk_msg_4 msg;
int ret;

// sanity checks
ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

msg.tod=message;
msg.datasize=(sizeof(int)<<2); // 4 integers
msg.data0=data0;
msg.data1=data1;
msg.data2=data2;
msg.data3=data3;

ret=c2gmskchain_add(sessid->m_chain,&msg,sizeof(msg));

return(ret);
}; // end function



/////////////////////////
// QUEUE NO_DATA IF NOTHING IN QUEUE
int queue_m_nodataifempty (session * sessid) {
// sanity checks
int ret;

ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

if (sessid->m_chain->numelem == 0) {
	ret=queue_m_msg_0(sessid,C2GMSK_MSG_NODATA);
	return(ret);
}; // end if


return(C2GMSK_RET_OK);
}; // end function


///////////////// DEMOD CHAIN

// queue MESSAGES: no additional data
int queue_d_msg_0 (session * sessid, int message) {
c2gmsk_msg_0 msg;
int ret;

// sanity checks
ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

msg.tod=message;
msg.datasize=0; // no data

ret=c2gmskchain_add(sessid->d_chain,&msg,sizeof(msg));

return(ret);
}; // end function

// queue MESSAGES: 1 datafield to send
int queue_d_msg_1 (session * sessid, int message, int data0) {
c2gmsk_msg_1 msg;
int ret;

// sanity checks
ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

msg.tod=message;
msg.datasize=sizeof(int); // 1 integer
msg.data0=data0;

ret=c2gmskchain_add(sessid->d_chain,&msg,sizeof(msg));

return(ret);
}; // end function

// queue MESSAGES: 2 datafield to send
int queue_d_msg_2 (session * sessid, int message, int data0, int data1) {
c2gmsk_msg_2 msg;
int ret;

// sanity checks
ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

msg.tod=message;
msg.datasize=(sizeof(int)<<1); // 2 integers
msg.data0=data0;
msg.data1=data1;

ret=c2gmskchain_add(sessid->d_chain,&msg,sizeof(msg));

return(ret);
}; // end function

// queue MESSAGES: 3 datafield to send
int queue_d_msg_3 (session * sessid, int message, int data0, int data1, int data2) {
c2gmsk_msg_3 msg;
int ret;

// sanity checks
ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

msg.tod=message;
msg.datasize=sizeof(int) + sizeof(int) + sizeof(int); // 3 integers
msg.data0=data0;
msg.data1=data1;
msg.data2=data2;

ret=c2gmskchain_add(sessid->d_chain,&msg,sizeof(msg));

return(ret);
}; // end function

// queue MESSAGES: 4 datafield to send
int queue_d_msg_4 (session * sessid, int message, int data0, int data1, int data2, int data3) {
c2gmsk_msg_4 msg;
int ret;

// sanity checks
ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

msg.tod=message;
msg.datasize=(sizeof(int)<<2); // 4 integers
msg.data0=data0;
msg.data1=data1;
msg.data2=data2;
msg.data3=data3;

ret=c2gmskchain_add(sessid->d_chain,&msg,sizeof(msg));

return(ret);
}; // end function



/////////////////////////
// QUEUE NO_DATA IF NOTHING IN QUEUE
int queue_d_nodataifempty (session * sessid) {
// sanity checks
int ret;

ret=checksign_sess(sessid);
if (ret != C2GMSK_RET_OK) {
	return(ret);
}; // end if

if (sessid->d_chain->numelem == 0) {
	ret=queue_d_msg_0(sessid,C2GMSK_MSG_NODATA);
	return(ret);
}; // end if


return(C2GMSK_RET_OK);
}; // end function



