#ifndef ERRORS_H
#define ERRORD_H

#define DATABASE_ERROR "Error: There was a problem connecting to the database. Please try again later.\n"
#define LOGIN_FATAL "\n\nWrong password!! or User Name\n"
#define REGISTRATION_ERROR "\n\nThe username you entered is already in use. Please choose a different one.\n"

#define ERROR_READING "❌ Error reading input. Please try again."
#define INVALID_INPUT "❌ Invalid input! Please enter a valid input."
#define INVALID_NUMBER_INPUT "❌ Invalid input! Only numbers are allowed."
#define OUT_OF_RANGE "❌ Error: Number out of range."
#define OVER_FLOW "❌ Error: Integer overflow/underflow."
#define ACCOUNT_DUP "❌ Error: This account already exists. Please enter a different number."
#define INVALID_DATE_FORMAT "❌ Invalid format! Please enter in MM/DD/YYYY format."
#define INVALID_YEAR "❌ Invalid year!."
#define INVALID_MONTH "❌ Invalid month! Enter a value between 1 and 12."
#define INVALID_DAY "❌ Invalid day! Enter a valid day for the given month."
#define INVALID_COUNTRY "❌ Invalid country! Enter a valid country.\nthe country must be lowercase.\n"
#define INVALID_ACCOUNT_TYPE "❌ Invalid account type! Enter a valid account type.\nthe account type must be lowercase.\n"
#define INVALID_PHONE_LENGTH "❌Error: Phone number must be between 7 and 20 digits.\n"
#define INVALIDE_ACCOUNT_ID_RANGE "❌Error: The account ID must be greater than or equal to 1."
#define INVALIDE_TRANSFER "❌Error: The user you entered already has an existing account with this ID.\nAccount transfer is not possible.\n"
#define INVALIDE_ACCOUNT_ID "\t\t❌Error: Account ID does not exist. Please enter a valid account.\n"
#define INVALIDE_USER "\n\t\t❌Error: The user you entered does not exist. Please check the username and try again.\n"
// #define INVALIDE_ "\t\t❌Error: "
// #define INVALIDE_ "\t\t❌Error: "
// #define INVALIDE_ "\t\t❌Error: "


#endif