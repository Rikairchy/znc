/*
 * Copyright (C) 2004-2010  See the AUTHORS file for details.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#ifndef _LISTENER_H
#define _LISTENER_H

#include "znc.h"

// Forward Declarations
class CRealListener;
// !Forward Declarations

class CListener {
public:
	typedef enum {
		ACCEPT_IRC,
		ACCEPT_HTTP,
		ACCEPT_ALL
	} AcceptType;

	CListener(unsigned short uPort, const CString& sBindHost, bool bSSL, EAddrType eAddr) {
		m_uPort = uPort;
		m_sBindHost = sBindHost;
		m_bSSL = bSSL;
		m_eAddr = eAddr;
		m_pListener = NULL;
		m_eAcceptType = ACCEPT_ALL;
	}

	~CListener();

	// Setters
	void SetSSL(bool b) { m_bSSL = b; }
	void SetAddrType(EAddrType eAddr) { m_eAddr = eAddr; }
	void SetPort(unsigned short u) { m_uPort = u; }
	void SetBindHost(const CString& s) { m_sBindHost = s; }
	void SetRealListener(CRealListener* p) { m_pListener = p; }
	void SetAcceptType(AcceptType a) { m_eAcceptType = a; }
	// !Setters

	// Getters
	bool IsSSL() const { return m_bSSL; }
	EAddrType GetAddrType() const { return m_eAddr; }
	unsigned short GetPort() const { return m_uPort; }
	const CString& GetBindHost() const { return m_sBindHost; }
	CRealListener* GetRealListener() const { return m_pListener; }
	AcceptType GetAcceptType() const { return m_eAcceptType; }
	// !Getters

	bool Listen();

private:
protected:
	bool            m_bSSL;
	EAddrType       m_eAddr;
	unsigned short  m_uPort;
	CString         m_sBindHost;
	CRealListener*  m_pListener;
	AcceptType      m_eAcceptType;
};

class CRealListener : public CZNCSock {
public:
	CRealListener(CListener *pParent) : CZNCSock(), m_pParent(pParent) {}
	virtual ~CRealListener();

	virtual bool ConnectionFrom(const CString& sHost, unsigned short uPort);
	virtual Csock* GetSockObj(const CString& sHost, unsigned short uPort);
	virtual void SockError(int iErrno);

private:
	CListener* m_pParent;
};

class CIncomingConnection : public CZNCSock {
public:
	CIncomingConnection(const CString& sHostname, unsigned short uPort, CListener::AcceptType eAcceptType);
	virtual ~CIncomingConnection() {}
	virtual void ReadLine(const CString& sData);

private:
	CListener::AcceptType m_eAcceptType;
};

#endif // !_LISTENER_H