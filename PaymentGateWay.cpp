#include <iostream>
#include <string>
#include <vector>

// Forward declaration of classes
class PaymentRequest;
class RefundRequest;
class Payment;
class Refund;
class TransactionLogger;

// Enumeration for PaymentMethod and TransactionStatus
enum class PaymentMethod { CREDIT_CARD, DEBIT_CARD, NET_BANKING, PAYPAL, OTHER };
enum class TransactionStatus { PENDING, SUCCESS, FAILURE, REFUNDED };

class CardInfo {
private:
    std::string cardNumber;
    std::string cardHolderName;
    std::string expirationDate;
    std::string cvv;

public:
    // Constructor
    CardInfo(const std::string& cardNumber, const std::string& cardHolderName, const std::string& expirationDate, const std::string& cvv)
        : cardNumber(cardNumber), cardHolderName(cardHolderName), expirationDate(expirationDate), cvv(cvv) {}

    // Getters
    std::string getCardNumber() const { return cardNumber; }
    std::string getCardHolderName() const { return cardHolderName; }
    std::string getExpirationDate() const { return expirationDate; }
    std::string getCvv() const { return cvv; }
};

class PaymentRequest {
private:
    std::string orderId;
    double amount;
    std::string currency;
    PaymentMethod paymentMethod;
    CardInfo cardInfo;
    std::string token;

public:
    // Constructor for card payments
    PaymentRequest(const std::string& orderId, double amount, const std::string& currency, PaymentMethod paymentMethod, const CardInfo& cardInfo)
        : orderId(orderId), amount(amount), currency(currency), paymentMethod(paymentMethod), cardInfo(cardInfo) {}

    // Constructor for tokenized payments
    PaymentRequest(const std::string& orderId, double amount, const std::string& currency, PaymentMethod paymentMethod, const std::string& token)
        : orderId(orderId), amount(amount), currency(currency), paymentMethod(paymentMethod), token(token) {}

    // Getters
    std::string getOrderId() const { return orderId; }
    double getAmount() const { return amount; }
    std::string getCurrency() const { return currency; }
    PaymentMethod getPaymentMethod() const { return paymentMethod; }
    CardInfo getCardInfo() const { return cardInfo; }
    std::string getToken() const { return token; }
};

class Transaction {
private:
    std::string transactionId;
    std::string orderId;
    TransactionStatus status;
    double amount;
    std::string currency;
    std::string timestamp;

public:
    Transaction(const std::string& transactionId, const std::string& orderId, TransactionStatus status, double amount, const std::string& currency, const std::string& timestamp)
        : transactionId(transactionId), orderId(orderId), status(status), amount(amount), currency(currency), timestamp(timestamp) {}

    std::string getTransactionId() const { return transactionId; }
    std::string getOrderId() const { return orderId; }
    TransactionStatus getStatus() const { return status; }
    double getAmount() const { return amount; }
    std::string getCurrency() const { return currency; }
    std::string getTimestamp() const { return timestamp; }
};

class Payment : public Transaction {
private:
    std::string paymentId;
    PaymentRequest paymentRequest;

public:
    Payment(const std::string& paymentId, const PaymentRequest& paymentRequest, TransactionStatus status, const std::string& timestamp)
        : Transaction(paymentId, paymentRequest.getOrderId(), status, paymentRequest.getAmount(), paymentRequest.getCurrency(), timestamp),
          paymentId(paymentId),
          paymentRequest(paymentRequest) {}

    std::string getPaymentId() const { return paymentId; }
    PaymentRequest getPaymentRequest() const { return paymentRequest; }
};

class Refund : public Transaction {
private:
    std::string refundId;
    RefundRequest refundRequest;

public:
    Refund(const std::string& refundId, const RefundRequest& refundRequest, TransactionStatus status, const std::string& timestamp)
        : Transaction(refundId, refundRequest.getOrderId(), status, refundRequest.getAmount(), refundRequest.getCurrency(), timestamp),
          refundId(refundId),
          refundRequest(refundRequest) {}

    std::string getRefundId() const { return refundId; }
    RefundRequest getRefundRequest() const { return refundRequest; }
};

class TransactionLogger {
public:
    void logPayment(const Payment& payment) {
        std::cout << "Payment logged: ID=" << payment.getPaymentId() << ", OrderID=" << payment.getOrderId() << ", Amount=" << payment.getAmount() << ", Status=" << static_cast<int>(payment.getStatus()) << ", Timestamp=" << payment.getTimestamp() << std::endl;
    }

    void logRefund(const Refund& refund) {
        std::cout << "Refund logged: ID=" << refund.getRefundId() << ", OrderID=" << refund.getOrderId() << ", Amount=" << refund.getAmount() << ", Status=" << static_cast<int>(refund.getStatus()) << ", Timestamp=" << refund.getTimestamp() << std::endl;
    }
};

class PaymentGateway {
private:
    std::string merchantId;
    std::string apiKey;
    TransactionLogger transactionLogger;

public:
    PaymentGateway(const std::string& merchantId, const std::string& apiKey)
        : merchantId(merchantId), apiKey(apiKey) {}

    void processPayment(const PaymentRequest& paymentRequest) {
        // Payment processing logic (not implemented in this simplified example)

        // Simulate successful payment
        std::string paymentId = generateUniqueID();
        std::string timestamp = getCurrentTimestamp();
        Payment payment(paymentId, paymentRequest, TransactionStatus::SUCCESS, timestamp);

        // Log payment transaction
        transactionLogger.logPayment(payment);
    }

    void processRefund(const RefundRequest& refundRequest) {
        // Refund processing logic (not implemented in this simplified example)

        // Simulate successful refund
        std::string refundId = generateUniqueID();
        std::string timestamp = getCurrentTimestamp();
        Refund refund(refundId, refundRequest, TransactionStatus::REFUNDED, timestamp);

        // Log refund transaction
        transactionLogger.logRefund(refund);
    }

    std::string generateUniqueID() {
        // Generate and return a unique ID (not implemented in this simplified example)
        return "UniqueID123";
    }

    std::string getCurrentTimestamp() {
        // Get and return the current timestamp (not implemented in this simplified example)
        return "2023-08-06 14:30:00";
    }
};

int main() {
    // Sample usage of the Payment Gateway

    PaymentGateway paymentGateway("merchant123", "api_key_456");

    // Sample payment request with card information
    CardInfo cardInfo("4111111111111111", "John Doe", "12/25", "123");
    PaymentRequest paymentRequestWithCard("order_123", 100.0, "USD", PaymentMethod::CREDIT_CARD, cardInfo);

    // Process the payment
    paymentGateway.processPayment(paymentRequestWithCard);

    // Sample payment request with a payment token (tokenized payment)
    std::string token = "payment_token_789";
    PaymentRequest paymentRequestWithToken("order_456", 50.0, "EUR", PaymentMethod::PAYPAL, token);

    // Process the tokenized payment
    paymentGateway.processPayment(paymentRequestWithToken);

    // Sample refund request for a previous payment
    RefundRequest refundRequest("order_123", 50.0, "USD");

    // Process the refund
    paymentGateway.processRefund(refundRequest);

    return 0;
}
