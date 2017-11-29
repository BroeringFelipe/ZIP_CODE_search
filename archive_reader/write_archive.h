/*
 ============================================================================
 Name        : write_archive.h
 Author      :
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura_arquivo.h"

#ifndef WRITE_ARCHIVE_H_INCLUDED
#define WRITE_ARCHIVE_H_INCLUDED

country_zip_code *organize_database(country_zip_code **countries, int countries_len);
void write_file(const char* file_path, country_zip_code* countries);

#endif // WRITE_ARCHIVE_H_INCLUDED
