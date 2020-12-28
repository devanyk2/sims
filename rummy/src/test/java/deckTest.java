import org.junit.Test;
import static org.junit.Assert.*;
import java.util.ArrayList;
import java.util.HashMap;

public class deckTest{
	/* checks to make sure the deck is proper size */
	@Test public void deck_constructor_validSize(){
		deck example = new deck();
		assertEquals(52, example.size());
	}

	/* checks to make sure no duplicate cards exist */
	@Test public void deck_constructor_noDupes(){
		deck example = new deck();
		HashMap<String, ArrayList<Integer>> test = new HashMap<String, ArrayList<Integer>>();
		while( example.size() > 0){			
			card c = example.deal();
			if (!(test.containsKey(c.suit))){		// If the suit doesnt currently exist 
				ArrayList<Integer> temp = new ArrayList<Integer>();
				temp.add(c.value);
				test.put(c.suit, temp);			
			}
			else{
				ArrayList<Integer> temp = test.get(c.suit); // If the suit exists
				assertFalse(temp.contains(c.value));        // Make sure it is the only number
				temp.add(c.value);		
				test.put(c.suit, temp);
			}
		}	
	}

	/* should be 13 cards per suit */
	@Test public void deck_constructor_validSuit(){
		deck example = new deck();
		HashMap<String, Integer> test = new HashMap<String, Integer>();
		while( example.size() > 0){
			card c = example.deal();
			if (!(test.containsKey(c.suit))){
				int temp = 1;
				test.put(c.suit, temp);
			}
			else{
				test.put(c.suit, temp);
			}
		}
		for(String k : test.keySet()){
			assertEqual(13, test.get(k));
		}

	}

	/* each suit should have the range 0-12 */
	@Test public void deck_constructor_validNumbers(){
	}

	/* test the deal function */
	@Test public void deck_deal_one(){
		deck example = new deck();
		card dealt = example.deal();
		assertEquals(51, example.size());
	}
	
	/* Test multiple deals */
	@Test public void deck_deal_mult(){
		deck example = new deck();
		card dealt1 = example.deal();
		card dealt2 = example.deal();
		assertEquals(50, example.size());
	}
}
