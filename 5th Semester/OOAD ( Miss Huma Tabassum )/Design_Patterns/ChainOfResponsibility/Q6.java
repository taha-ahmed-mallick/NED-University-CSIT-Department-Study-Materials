public class OnlineOrderingSystem {

    public static void main(String[] args) {
        AuthSystem authsystem = new AuthSystem();

        AuthRequest request1 = new AuthRequest("admin", "password123", null);
        authsystem.processAuth(request1);
        AuthRequest request2 = new AuthRequest(null, null, "validtoken123");
        authsystem.processAuth(request2);
    }
}


class AuthRequest {
    private String username;
    private String password;
    private String token;

    public AuthRequest(String username, String password, String token) {
        this.username = username;
        this.password = password;
        this.token = token;
    }

    public String getUsername() { return username; }
    public String getPassword() { return password; }
    public String getToken() { return token; }
}


// Handler Interface
interface AuthHandler {
    void setNextHandler(AuthHandler nextHandler);
    void authenticate(AuthRequest request);
}

class BasicAuthHandler implements AuthHandler {
    private AuthHandler nextHandler;

    @Override
    public void setNextHandler(AuthHandler nextHandler) {
        this.nextHandler = nextHandler;
    }

    @Override
    public void authenticate(AuthRequest request) {
        if (request.getUsername() != null && request.getPassword() != null) {
            if ("admin".equals(request.getUsername()) &&
                "password123".equals(request.getPassword())) {

                System.out.println("Basic Authentication Successful!");

            } 
            else
                System.out.println("Basic Authentication Failed – Invalid credentials!");
        } 
        else
            System.out.println("Basic Auth Skipped – No username/password provided.");

        if (nextHandler != null)
            nextHandler.authenticate(request) ;
    }
}

class TokenAuthHandler implements AuthHandler {
    private AuthHandler nextHandler;

    @Override
    public void setNextHandler(AuthHandler nextHandler) {
        this.nextHandler = nextHandler;
    }

    @Override
    public void authenticate(AuthRequest request) {
        if (request.getToken() != null) {

            if ("validtoken123".equals(request.getToken()))
                System.out.println("Token Authentication Successful!");
            else
                System.out.println("Token Authentication Failed – Invalid Token!");
        } 
        else
            System.out.println("Token Auth Skipped – No token provided.");

        if (nextHandler != null)
            nextHandler.authenticate(request);
    }
}


// AuthSystem (Client)
class AuthSystem {
    private AuthHandler chain;

    public AuthSystem() {
        AuthHandler basicAuth = new BasicAuthHandler();
        AuthHandler tokenAuth = new TokenAuthHandler();

        basicAuth.setNextHandler(tokenAuth);
        this.chain = basicAuth;
    }

    public void processAuth(AuthRequest request) {
        System.out.println("\nProcessing authentication request...");
        chain.authenticate(request);
        System.out.println("Authentication process completed.\n");
    }
}