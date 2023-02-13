#include "Utils.h"
#include "HTTPClient.h"

String Utils::getDownloadURL(String url)
{
  HTTPClient http;

  http.begin(url);

  const char *headerKeys[] = {"location"};
  http.collectHeaders(headerKeys, 1);

  int code = http.GET();

  if (code != 302)
    return String(NULL);

  String downloadURL = http.header("location");

  http.end();

  return downloadURL;
}

void Utils::downloadFile(String url, String fileName)
{
  HTTPClient http;
  http.begin(getDownloadURL(url));
  http.useHTTP10(true);
  int code = http.GET();

  if (code != 200)
    return;

  saveFileFromStream(http, "/dist/" + fileName);

  http.end();
}