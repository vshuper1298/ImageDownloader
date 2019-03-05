#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

const QString searchQuery = "https://www.googleapis.com/customsearch/v1?q=%1&start=%2&cx=001678308346640452026:buokl5p6twm&searchType=image&key=AIzaSyBN8Mp85VX9s-0PlVZhy59p8UJlOJ8BseQ";
const QString customSearchUrl = "https://www.googleapis.com/customsearch/";
const int bufferSize = 512;
const int imagesViewCount = 9;
const int maxRequestCount = 6;
const int startSearchIndex = 1;
const int resultsPerRequest = 10;

#endif // CONSTANTS_H
