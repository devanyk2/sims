import java.util.ArrayList;

public class deck{
	private ArrayList<card> cards = new ArrayList<card>();

	public deck(){
		String[] suits = {"h", "d", "s", "c"};
		for(String s : suits){			//for every suit, create 13 cards
			int num = 0;
			card c = new card(num, s);
			cards.add(c);
			num++;
			while((num % 13) != 0){		//switch suit on the 14th iteration
				c = new card(num, s);
				cards.add(c);
				num++;
			}
		}
	}

	public int size(){
		return this.cards.size();
	}
	/* returns a card from the top of the deck */
	public card deal(){
		return this.cards.remove(0);
	}
}
