typedef unsigned char BYTE;
typedef unsigned char UINT8;
typedef unsigned short UINT16;

enum UnicodeType {
  AutoType = 0,
  Binary = 1,
  Ansi = 2,
  Unicode_Le = 3,
  Unicode_Be = 4,
  UTF8 = 5
};
static int nullByteCount = 2;
// https://github.com/stefankueng/sktoolslib/blob/11f1ecabcb3e876adb878b966b2ce65f5772de9e/TextFile.cpp#L414
UnicodeType CheckUnicodeType(BYTE *pBuffer, int cb) {
  if (cb < 2)
    return Ansi;
  UINT16 *pVal16 = reinterpret_cast<UINT16 *>(pBuffer);
  UINT8 *pVal8 = reinterpret_cast<UINT8 *>(pVal16 + 1);
  // scan the whole buffer for a 0x0000 sequence
  // if found, we assume a binary file
  int nNull = 0;
  int nDblNull = 0;
  for (int i = 0; i < (cb - 2); i = i + 2) {
    if (0x0000 == *pVal16++)
      ++nDblNull;
    if (0x00 == *pVal8++)
      ++nNull;
    if (0x00 == *pVal8++)
      ++nNull;
  }
  if (nDblNull > nullByteCount) // configured value: allow double null chars to
                                // account for 'broken' text files
    return Binary;
  pVal16 = reinterpret_cast<UINT16 *>(pBuffer);
  pVal8 = reinterpret_cast<UINT8 *>(pVal16 + 1);
  if (*pVal16 == 0xFEFF)
    return Unicode_Le;
  if (*pVal16 == 0xFFFE)
    return Unicode_Be;
  if ((nNull > 3) &&
      ((cb % 2) ==
       0)) // arbitrary value: allow three null chars to account for 'broken'
           // ANSI/UTF8 text files, otherwise consider the file UTF16-LE
    return Unicode_Le;
  if (cb < 3)
    return Ansi;
  if (*pVal16 == 0xBBEF) {
    if (*pVal8 == 0xBF)
      return UTF8;
  }
  // check for illegal UTF8 chars
  pVal8 = static_cast<UINT8 *>(pBuffer);
  for (int i = 0; i < cb; ++i) {
    if ((*pVal8 == 0xC0) || (*pVal8 == 0xC1) || (*pVal8 >= 0xF5))
      return Ansi;
    pVal8++;
  }
  pVal8 = static_cast<UINT8 *>(pBuffer);
  bool bUTF8 = false;
  for (int i = 0; i < (cb - 4); ++i) {
    if ((*pVal8 & 0xE0) == 0xC0) {
      pVal8++;
      i++;
      if ((*pVal8 & 0xC0) != 0x80)
        return Ansi;
      bUTF8 = true;
    }
    if ((*pVal8 & 0xF0) == 0xE0) {
      pVal8++;
      i++;
      if ((*pVal8 & 0xC0) != 0x80)
        return Ansi;
      pVal8++;
      i++;
      if ((*pVal8 & 0xC0) != 0x80)
        return Ansi;
      bUTF8 = true;
    }
    if ((*pVal8 & 0xF8) == 0xF0) {
      pVal8++;
      i++;
      if ((*pVal8 & 0xC0) != 0x80)
        return Ansi;
      pVal8++;
      i++;
      if ((*pVal8 & 0xC0) != 0x80)
        return Ansi;
      pVal8++;
      i++;
      if ((*pVal8 & 0xC0) != 0x80)
        return Ansi;
      bUTF8 = true;
    }
    pVal8++;
  }
  if (bUTF8)
    return UTF8;
  return Ansi;
}
extern "C" int AutoDectUnicodeType(const BYTE *pBuffer, int cb) {
  return (int)CheckUnicodeType((BYTE *)pBuffer, cb);
}
