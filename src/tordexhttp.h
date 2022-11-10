#pragma once

#include <Windows.h>
#include <winhttp.h>
#include <stdlib.h>
#include <vector>
#include <string>

namespace tordex
{
	class http_request
	{
		friend class http;
	public:
		typedef std::vector<http_request*>	vector;
	protected:
		HINTERNET			m_hConnection;
		HINTERNET			m_hRequest;
		http*				m_http;
		BYTE				m_buffer[8192];
		DWORD				m_error;
		ULONG64				m_content_length;
		ULONG64				m_downloaded_length;
		DWORD				m_status;
		std::wstring		m_url;
	public:
		http_request();
		virtual ~http_request();

		virtual void OnFinish(DWORD dwError, LPCWSTR errMsg) = 0;
		virtual void OnData(LPCBYTE data, DWORD len, ULONG64 downloaded, ULONG64 total) = 0;
		virtual void OnHeadersReady(HINTERNET hRequest);

		BOOL	create(LPCWSTR url, HINTERNET hSession);
		void	cancel();
		ULONG64	get_content_length();
		DWORD	get_status_code();

	protected:
		DWORD	onSendRequestComplete();
		DWORD	onHeadersAvailable();
		DWORD	onHandleClosing();
		DWORD	onRequestError(DWORD dwError);
		DWORD	onReadComplete(DWORD len);
		DWORD	readData();
		void	set_parent(http* parent);
	};

	class http
	{
		friend class http_request;

		HINTERNET				m_hSession;
		http_request::vector	m_requests;
		CRITICAL_SECTION		m_sync;
		DWORD					m_maxConnectionsPerServer;
	public:
		http();
		virtual ~http();

		void	set_max_connections_per_server(DWORD max_con);
		BOOL	open(LPCWSTR pwszUserAgent, DWORD dwAccessType, LPCWSTR pwszProxyName, LPCWSTR pwszProxyBypass);
		BOOL	download_file(LPCWSTR url, http_request* request);
		void	stop();
		void	close();

	private:
		static VOID CALLBACK http_callback(HINTERNET hInternet, DWORD_PTR dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength);

	protected:
		void remove_request(http_request* request);
	};

	inline DWORD http_request::get_status_code()
	{
		return m_status;
	}

	inline ULONG64	http_request::get_content_length()
	{
		return m_content_length;
	}

	inline void http::set_max_connections_per_server(DWORD max_con)
	{
		m_maxConnectionsPerServer = max_con;
	}

}