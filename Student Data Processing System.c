/*
This program processes a CSV file based on setup parameters received from a given JSON file.
It reads each student record from the CSV file, converts it to a binary file, and then converts it to XML format.
Finally, it validates the generated XML file against an XML Schema Definition (XSD) file.*/

/*
Use:
gcc 2020510050_2021510102_2021510039.c -o out -I/usr/include/libxml2 -lxml2 -ljson-c
gcc as.c -o out -I/usr/include/libxml2 -lxml2 -ljson-c
./out setupParams.json records.csv
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <json-c/json.h>
#include <stdint.h>
#include <libxml/xmlschemastypes.h>

// Structure to hold student information
typedef struct {
    char name[20];
    char surname[30];
    char stuID[11];
    char gender[2];
    char email[60]; // Note: Email is an optional field.
    char phone[20];
    char letter_grade[3];
    char midterm[4];
    char project[4];
    char final[4];
    char regularStudent[5]; // To accommodate an emoji plus null terminator.
    char course_surveyRating[2];
} StudentInfo;

// Structure to hold setup parameters from a JSON configuration file
typedef struct {
    char dataFileName[50];
    int keyStart;
    int keyEnd;
    char order[4]; // "ASC" or "DESC" for sorting
} SetupParams;

int countOfData = 0;

// Function to read setup parameters from JSON file
SetupParams readSetupParams(const char* filename) {
    SetupParams params;
    
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open JSON file");
        exit(EXIT_FAILURE);
    }
    
    char buffer[1024];
    fread(buffer, 1024, 1, fp);
    fclose(fp);
    
    //json is parsed.
    struct json_object *parsed_json = json_tokener_parse(buffer);
    json_object *jDataFileName, *jOrder, *jKeyStart, *jKeyEnd;
    
    json_object_object_get_ex(parsed_json, "dataFileName", &jDataFileName);
    json_object_object_get_ex(parsed_json, "keyStart", &jKeyStart);
    json_object_object_get_ex(parsed_json, "keyEnd", &jKeyEnd);
    json_object_object_get_ex(parsed_json, "order", &jOrder);
    
    //
    strcpy(params.dataFileName, json_object_get_string(jDataFileName));
    params.keyStart = json_object_get_int(jKeyStart);
    params.keyEnd = json_object_get_int(jKeyEnd);
    strcpy(params.order, json_object_get_string(jOrder));
   
    return params;
}

int strToInt(const char *str){
    char *endptr;
    int value = strtol(str,&endptr,10);

    return value;
}

// Function to convert integer values to Big and Little Endian hex strings
void convertToEndianHex(char* hexBE, char* hexLE, char* decimal, char* str) {
    
    int value = strToInt(str);

    // Calculate hexadecimal value in big endian format
    sprintf(hexBE, "%02X%02X%02X%02X",
            (value >> 24) & 0xFF,
            (value >> 16) & 0xFF,
            (value >> 8) & 0xFF,
            value & 0xFF);
    
    // Calculate hexadecimal value in little endian format
    sprintf(hexLE, "%02X%02X%02X%02X",
            value & 0xFF,
            (value >> 8) & 0xFF,
            (value >> 16) & 0xFF,
            (value >> 24) & 0xFF);

    //Decimal
    char *ptr;
    long decimalValue = strtol(hexLE, &ptr, 16);
    sprintf(decimal, "%u", decimalValue);
}

void getBytesFromBinary(char data[], int startByte, int endByte, char result[]) {
    size_t i,j;
   
    for (i = startByte, j = 0; i <= endByte; i++, j++) {
        result[j] = data[i];
    }
}

void bubbleSortStudents(char binaryData[][sizeof(StudentInfo)], int countOfData, SetupParams params) {
    // Correcting the ascending flag; true for "ASC", false for "DESC"
    bool ascending = strcmp(params.order, "ASC") == 0;
    int wordByte = params.keyEnd - params.keyStart + 1;

    for (int i = 0; i < countOfData - 1; ++i) {
        for (int j = 0; j < countOfData - i - 1; ++j) {
            char first[wordByte + 1], second[wordByte + 1]; // +1 for null-terminator
            getBytesFromBinary(binaryData[j], params.keyStart, params.keyEnd, first);
            getBytesFromBinary(binaryData[j+1], params.keyStart, params.keyEnd, second);

            first[wordByte] = '\0';  // Ensure null-termination
            second[wordByte] = '\0'; // Ensure null-termination
            
            // Adjust comparison based on sort order
            bool shouldSwap = ascending ? (strcmp(first, second) > 0) : (strcmp(first, second) < 0);

            if (shouldSwap) {    
                char temp[sizeof(StudentInfo)];
                memcpy(temp, binaryData[j], sizeof(StudentInfo));
                memcpy(binaryData[j], binaryData[j+1], sizeof(StudentInfo));
                memcpy(binaryData[j+1], temp, sizeof(StudentInfo));
            }
        }
    }
}

void parseAndAssignField(StudentInfo* student, int fieldIndex, const char* token) {
    int success;
    switch (fieldIndex) {
        case 0: strncpy(student->name, token, sizeof(student->name) - 1); break;
        case 1: strncpy(student->surname, token, sizeof(student->surname) - 1); break;
        case 2: strncpy(student->stuID, token, sizeof(student->stuID) - 1); break;
        case 3: strncpy(student->gender, token, sizeof(student->gender) - 1); break;
        case 4: strncpy(student->email, token, sizeof(student->email) - 1); break;
        case 5: strncpy(student->phone, token, sizeof(student->phone) - 1); break;
        case 6: strncpy(student->letter_grade, token, sizeof(student->letter_grade) - 1); break;
        case 7: strncpy(student->midterm, token, sizeof(student->midterm) - 1); break;
        case 8: strncpy(student->project, token, sizeof(student->project) - 1); break;
        case 9: strncpy(student->final, token, sizeof(student->final) - 1); break;
        case 10: strncpy(student->regularStudent, token, sizeof(student->regularStudent) - 1); break;
        case 11: strncpy(student->course_surveyRating, token, sizeof(student->course_surveyRating) - 1); break;
    }
}

// Enhanced CSV to Binary function with robust parsing for optional fields and emojis
void csvToBinary(const char* csvFile, const char* binaryFile) {
    FILE* csvFp = fopen(csvFile, "r");
    if (!csvFp) {
        perror("Failed to open CSV file");
        exit(EXIT_FAILURE);
    }

    FILE* binFp = fopen(binaryFile, "wb");
    if (!binFp) {
        perror("Failed to open binary file for writing");
        fclose(csvFp);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), csvFp); // Skip CSV header

    while (fgets(buffer, sizeof(buffer), csvFp)) {
        StudentInfo student = {0}; // Initialize the student record with zeros

        // Manual tokenization to correctly handle empty fields
        char* start = buffer;
        char* end = NULL;
        int fieldIndex = 0;
        while ((end = strpbrk(start, ",\n")) != NULL) {
            *end = '\0'; // Temporarily terminate the current token
            parseAndAssignField(&student, fieldIndex++, start);
            start = end + 1; // Move past the comma or newline
        }
        if (*start) { // Handle the last field if it's not empty
            parseAndAssignField(&student, fieldIndex, start);
        }

        fwrite(&student, sizeof(student), 1, binFp);
        countOfData++;
    }

    fclose(csvFp);
    fclose(binFp);
}


// Function to convert the sorted binary data to XML format
void binaryToXML(const char* binaryFile, const char* xmlFile, SetupParams params) {
    FILE* binFp = fopen(binaryFile, "rb");
    if (!binFp) {
        perror("Failed to open binary file");
        exit(EXIT_FAILURE);
    }

    int arraySize = countOfData, dataSize = sizeof(StudentInfo);
    char binaryData[arraySize][dataSize]; // Array to store data

    // Read binary data into memory
    for (int i = 0; i < arraySize; i++) {
        fread(binaryData[i], 1, dataSize, binFp);
    }
    fclose(binFp);

    // Sort the binary data
    bubbleSortStudents(binaryData, arraySize, params);

    // Create XML document and root node
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "records");
    xmlDocSetRootElement(doc, root_node);

    StudentInfo students;

    char idStr[12], hexBE[9], hexLE[9], decimal[9];
    // Iterate through sorted data to convert each entry to XML
    for (size_t i = 0; i < countOfData; ++i) {
        memcpy(&students, binaryData[i], sizeof(StudentInfo));
        xmlNodePtr row = xmlNewChild(root_node, NULL, BAD_CAST "row", NULL);
        sprintf(idStr, "%zu", i + 1); // Convert index to string for ID
        xmlNewProp(row, BAD_CAST "id", BAD_CAST idStr);

        // Student Info Section
        xmlNodePtr student_info = xmlNewChild(row, NULL, BAD_CAST "student_info", NULL);
        xmlNewChild(student_info, NULL, BAD_CAST "name", BAD_CAST students.name);
        xmlNewChild(student_info, NULL, BAD_CAST "surname", BAD_CAST students.surname);
        xmlNewChild(student_info, NULL, BAD_CAST "stuID", BAD_CAST students.stuID);
        xmlNewChild(student_info, NULL, BAD_CAST "gender", BAD_CAST students.gender);
        // Optional email field: Check if empty before adding
        if (strlen(students.email) > 0) {
            xmlNewChild(student_info, NULL, BAD_CAST "email", BAD_CAST students.email);
        }
        xmlNewChild(student_info, NULL, BAD_CAST "phone", BAD_CAST students.phone);

        // Grade Info Section
        xmlNodePtr grade_info = xmlNewChild(row, NULL, BAD_CAST "grade_info", NULL);
        xmlNewProp(grade_info, BAD_CAST "letter_grade", BAD_CAST students.letter_grade);
        xmlNewChild(grade_info, NULL, BAD_CAST "midterm", BAD_CAST students.midterm);
        xmlNewChild(grade_info, NULL, BAD_CAST "project", BAD_CAST students.project);
        xmlNewChild(grade_info, NULL, BAD_CAST "final", BAD_CAST students.final);

        // Regular Student (potentially an emoji)
        xmlNewChild(row, NULL, BAD_CAST "regularStudent", BAD_CAST students.regularStudent);

        // Course Survey Rating
        xmlNodePtr ratingNode = xmlNewChild(row, NULL, BAD_CAST "course_surveyRating", NULL);
        convertToEndianHex(hexBE, hexLE, decimal,students.course_surveyRating);
        xmlNewProp(ratingNode, BAD_CAST "hexVal_bigEnd", BAD_CAST hexBE);
        xmlNewProp(ratingNode, BAD_CAST "hexVal_littleEnd", BAD_CAST hexLE);
        xmlNewProp(ratingNode, BAD_CAST "decimal", BAD_CAST decimal);
        xmlNodeSetContent(ratingNode, BAD_CAST students.course_surveyRating);
    }

    // Save XML document to file
    xmlSaveFormatFileEnc(xmlFile, doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}


void XSDvalidateXML(char * inXML, char * inXSD) {
    xmlDocPtr doc;
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt;
	
    char *XMLFileName = inXML; // write your xml file here
    char *XSDFileName = inXSD; // write your xsd file here
    
    xmlLineNumbersDefault(1); //set line numbers, 0> no substitution, 1>substitution
    ctxt = xmlSchemaNewParserCtxt(XSDFileName); //create an xml schemas parse context
    schema = xmlSchemaParse(ctxt); //parse a schema definition resource and build an internal XML schema
    xmlSchemaFreeParserCtxt(ctxt); //free the resources associated to the schema parser context
    
    doc = xmlReadFile(XMLFileName, NULL, 0); //parse an XML file
    if (doc == NULL)
    {
        fprintf(stderr, "Could not parse %s\n", XMLFileName);
    }
    else
    {
        xmlSchemaValidCtxtPtr ctxt;  //structure xmlSchemaValidCtxt, not public by API
        int ret;
        
        ctxt = xmlSchemaNewValidCtxt(schema); //create an xml schemas validation context 
        ret = xmlSchemaValidateDoc(ctxt, doc); //validate a document tree in memory
        if (ret == 0) //validated
        {
            printf("%s validates\n", XMLFileName);
        }
        else if (ret > 0) //positive error code number
        {
            printf("%s fails to validate\n", XMLFileName);
        }
        else //internal or API error
        {
            printf("%s validation generated an internal error\n", XMLFileName);
        }
        xmlSchemaFreeValidCtxt(ctxt); //free the resources associated to the schema validation context
        xmlFreeDoc(doc);
    }
    // free the resource
    if(schema != NULL)
        xmlSchemaFree(schema); //deallocate a schema structure

    xmlSchemaCleanupTypes(); //cleanup the default xml schemas types library
    xmlCleanupParser(); //cleans memory allocated by the library itself 
    xmlMemoryDump(); //memory dump
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <setupParams.json> <inputCSV.csv>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    SetupParams params = readSetupParams(argv[1]);

    csvToBinary(argv[2], params.dataFileName);
    binaryToXML(params.dataFileName, "outputXML.xml", params); 
    XSDvalidateXML("outputXML.xml", "2020510050_2021510102_2021510039.xsd");

    printf("Conversion complete.\n");
    return 0;
}