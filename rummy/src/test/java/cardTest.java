import org.junit.Test;
import static org.junit.Assert.*;

public class cardTest{

	@Test public void card_constructor_validNumber(){
		card example = new card(1, "h");
		assertEquals(1, example.value);
	}
	@Test public void card_constructor_validSuite(){
		card example = new card(1, "h");
		assertTrue("h".equals(example.suit));
	}
	@Test public void card_constructor_invalidNumber(){
		Exception exception = assertThrows(IllegalArgumentException.class,  () -> {new card(-11, "h");});
		assertTrue("Invalid Number".equals(exception.getMessage()));
	}
	@Test public void card_constructor_invalidSuit(){
		Exception exception = assertThrows(IllegalArgumentException.class,  () -> {new card(1, "a");});
		assertTrue("Invalid Suit".equals(exception.getMessage()));
	}
}
