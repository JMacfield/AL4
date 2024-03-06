//#include <cpprest/filestream.h>
//#include <cpprest/http_client.h>
//
//using namespace utility;			   // ユーティリティ
//using namespace web;				   // URI共通機能
//using namespace web::http;			   // 共通HTTP機能
//using namespace web::http::client;	   // HTTP クライアント機能
//using namespace concurrency::streams;  // 非同期ストリーム
//
////template <class T>
//pplx::task<T> Get(const std::wstring& url) {
//	return pplx::create_task([=] {
//		http_client client(url);
//		return client.request(methods::GET);
//		})
//		.then([](http_response response) {
//			if (response.status_code() == status_codes::OK) {
//				return response.extract_json();
//			}
//			});
//}
//
//pplx::task<int> Post(const std::wstring& url) {
//	return pplx::create_task([=] {
//		json::value postData;
//		postData[L"name"] = json::value::string(L"arguments");
//
//		http_client client(url);
//		return client.request(methods::POST, L"",
//			postData.serialize(), L"application/json"); })
//
//		.then([](http_response response) {
//			if (response.status_code() == status_codes::OK) {
//				return response.extract_json();
//			} })
//
//			.then([](json::value json) {
//				return json[L"ServerStatus"].as_integer(); });
//}