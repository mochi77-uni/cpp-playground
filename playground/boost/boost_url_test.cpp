
#include <boost/url/parse.hpp>
#include <boost/url/url.hpp>
#include <print>

int main() {
	using namespace boost::urls;
	const url_view uv("https://www.sitataka.jp/path/to/unti.txt?id=36&name=mamejiro&genbaneko#donghuan");

	std::println("{}", uv.data());
	for (auto [key, value, _] : uv.params()) {
		std::println("[{}] = {} ({})", key, value, _);
	}

	url u{uv};
	u.set_scheme("http")
	 .set_encoded_host("www.sitataka.kr")
	 .remove_query()
	 .remove_fragment()
	 .params().append({"id", "nazoseibutu"});
	std::println("{}", u.data());

	return 0;
}