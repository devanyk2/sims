import java.util.ArrayList;
import java.util.Arrays;

public class card{
	public int value;
	public String suit;

	public card(int value, String suit){
		String message = isInvalid(value, suit);
		if (message != null){
			throw new IllegalArgumentException(message);
		}
		this.value = value;
		this.suit = suit;
	}
	/* Determines validity of input */
	private String isInvalid(int value, String suit){
		ArrayList<String> allowedString = new ArrayList<String>(Arrays.asList("s","c","d","h"));
		if ((value < 0) || (value > 12)){
			return "Invalid Number";
		}
		if (!(allowedString.contains(suit))){
			return "Invalid Suit ";
		}
		return null; 					
	}

}
