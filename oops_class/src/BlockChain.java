import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;

class Block {
    final String data;
    final byte[] previousHash;
    byte[] hash;

    private Block(String data, byte[] previousHash) {
        this.data = data;
        this.previousHash = Arrays.copyOf(previousHash, previousHash.length);
    }

    static Block createBlock(String data, byte[] previousHash) {
        Block block = new Block(data, previousHash);
        byte[] data_hash = data.getBytes(StandardCharsets.UTF_8);
        byte[] hash = new byte[data_hash.length + previousHash.length];
        for (int i=0; i<hash.length; i++) {
            hash[i]
        }
    }
}

public class BlockChain {
    Block[] chain;

    public static void main(String[] args) {
        try {
            System.out.println(toSha256("naman"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static byte[] toSha256(String val) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        return md.digest(val.getBytes(StandardCharsets.UTF_8));
    }

    public static String byteToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b: bytes) {
            sb.append(String.format("%x", b));
        }
        return sb.toString();
    }
}
