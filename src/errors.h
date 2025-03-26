#ifndef ERRORS_H
#define ERRORD_H

#define DATABASE_ERROR "Error: There was a problem connecting to the database. Please try again later.\n"
#define LOGIN_FATAL "\n\nWrong password!! or User Name\n"
#define REGISTRATION_ERROR "\n\nThe username you entered is already in use. Please choose a different one.\n"

#define ERROR_READING "\t\t❌ Error reading input. Please try again."
#define INVALID_INPUT "\t\t❌ Invalid input! Please enter a valid input."
#define INVALID_NUMBER_INPUT "\t\t❌ Invalid input! Only numbers are allowed."
#define OUT_OF_RANGE "\t\t❌ Error: Number out of range."
#define OVER_FLOW "\t\t❌ Error: Integer overflow/underflow."
#define ACCOUNT_DUP "\t\t❌ Error: This account already exists. Please enter a different number."
#define INVALID_DATE_FORMAT "\t\t❌ Invalid format! Please enter in MM/DD/YYYY format."
#define INVALID_YEAR "\t\t❌ Invalid year!."
#define INVALID_MONTH "\t\t❌ Invalid month! Enter a value between 1 and 12."
#define INVALID_DAY "\t\t❌ Invalid day! Enter a valid day for the given month."
#define INVALID_COUNTRY "\t\t❌ Invalid country! Enter a valid country.\nthe country must be lowercase.\n"
#define INVALID_ACCOUNT_TYPE "\t\t❌ Invalid account type! Enter a valid account type.\nthe account type must be lowercase.\n"
#define INVALID_PHONE_LENGTH "\t\t❌Error: Phone number must be between 7 and 20 digits.\n"
#define INVALIDE_ACCOUNT_ID_RANGE "\t\t❌Error: The account ID must be greater than or equal to 1."
#define INVALIDE_TRANSFER "\t\t❌Error: The user you entered already has an existing account with this ID.\nAccount transfer is not possible.\n"
#define INVALIDE_ACCOUNT_ID "\t\t❌Error: Account ID does not exist. Please enter a valid account.\n"
#define INVALIDE_USER "\n\t\t❌Error: The user you entered does not exist. Please check the username and try again.\n"
// #define INVALIDE_ "\t\t❌Error: "
// #define INVALIDE_ "\t\t❌Error: "
// #define INVALIDE_ "\t\t❌Error: "


#endif