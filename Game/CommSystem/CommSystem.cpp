//#include "CommSystem.h"
//
//template <class T>
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