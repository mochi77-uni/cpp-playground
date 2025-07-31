
#include <string>
#include <print>
#include <iostream>
#include <cstring>
#include <memory>

#include <libxml/HTMLparser.h>

inline const char* toCString(const xmlChar* s) {
	return reinterpret_cast<const char *>(s);
}

xmlNodePtr traverseDomTrees(xmlNodePtr node) {
	if (!node) return nullptr;

	for (auto currentNode = node; currentNode; currentNode = currentNode->next) {
		if (currentNode->type == XML_ELEMENT_NODE && strcmp(toCString(currentNode->name), "title") == 0) {
			return currentNode;
		}
		if (auto traverseResult = traverseDomTrees(currentNode->children); traverseResult)
			return traverseResult;
	}

	return nullptr;
}

std::string getHtmlTitle(const std::string_view& html_source) {
	const std::unique_ptr<xmlDoc, decltype(&xmlFreeDoc)> doc{
		htmlReadMemory(html_source.data(), html_source.size(), nullptr, "utf-8", HTML_PARSE_NOERROR),
		xmlFreeDoc
	};

	const auto root = xmlDocGetRootElement(doc.get());
	if (root == nullptr) return "";

	const auto titleNode = traverseDomTrees(root);
	if (titleNode && titleNode->children && titleNode->children->content)
		return {toCString(titleNode->children->content)};

	return "";
}

int main() {
	constexpr std::string_view htmlSource =
	R"(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>My Website</title>
    <link rel="stylesheet" href="./style.css">
    <link rel="icon" href="./favicon.ico" type="image/x-icon">
  </head>
  <body>
    <main>
        <h1>Welcome to My Website</h1>
    </main>
    <script src="index.js"></script>
  </body>
</html>
	)";

	std::println("{}", getHtmlTitle(htmlSource));

	return 0;
}
