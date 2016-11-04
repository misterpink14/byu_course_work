CREATE TABLE recipe (
	recipe_id INTEGER PRIMARY KEY AUTOINCREMENT, 
	title TEXT, 
	description BLOB
);

INSERT INTO recipe (title, description) VALUES ("Fry Bread", "A fried flat dough");
INSERT INTO recipe (title, description) VALUES ("Navajo Taco", "A flat taco made with Fry Bread");
INSERT INTO recipe (title, description) VALUES ("Mutton Stew", "Stew made with mutton meat");
INSERT INTO recipe (title, description) VALUES ("Blood Sausage", "Sausage made from sheep blood");
INSERT INTO recipe (title, description) VALUES ("Blue Corn", "A thick corn meal mush");

CREATE TABLE ingredient (
	ingredient_id INTEGER PRIMARY KEY AUTOINCREMENT, 
	name TEXT, 
	quantity INTEGER, 
	recipe INTEGER,
	FOREIGN KEY(recipe) REFERENCES recipe(recipe_id)
);


INSERT INTO ingredient (name, quantity, recipe) VALUES ("Unbleached Flour", "1 Cup", 1);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Salt", "1/4 Tsp", 1);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Powdered Milk", "1 Tsp", 1);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Baking Powder", "1 Tsp", 1);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Water", "1/2 Cup", 1);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Vegetable Oil or lard", "", 1);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Extra flour to flour hands", "", 1);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Lean Ground Meat(beef, lamb, venison, pork)", "1 Pound", 2);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Diced Onion", "1 Cup", 2);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Fry Bread", "4", 2);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Iceburg Lettuce", "1 head", 2);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Tomatoes, diced", "3", 2);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Shredded Sharp Cheddar Cheese", "2 Cups", 2);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Diced Green Chiles, drained", "1 (3-ounce) Can", 2);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Sour Cream (optional)", "", 2);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Mutton/Lamb Chops", "1 1/2 Pounds", 3);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Potatoes (Medium)", "4-5", 3);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Onion (Medium)", "1", 3);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Dumplings or Egg Noodles", "", 3);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Black Pepper", "1/2 Tsp", 3);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Cut Up Carrot", "1 Cup", 3);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Chopped Celery", "1 Cup", 3);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Sheep blood", "1 Pound", 4);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Fat, diced", "1/2 Pound", 4);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Cornmeal", "1/2 Pound", 4);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Cooked and Diced Potato", "1", 4);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Onion, finely chopped", "1/2", 4);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Green Chile", "1", 4);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Salt", "3 Tsp", 4);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Black Pepper", "1 Tsp", 4);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Sheep Stomachs or Largest Hog Castings", "38-42mm", 4);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Water", "4 Cups", 5);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Juniper Ashes", "1 Tbsp", 5);
INSERT INTO ingredient (name, quantity, recipe) VALUES ("Roasted Blue Cornmeal", "1 Cup", 5);



CREATE TABLE instruction (
	instruction_id INTEGER PRIMARY KEY AUTOINCREMENT, 
	body TEXT, 
	recipe INTEGER,
	FOREIGN KEY(recipe) REFERENCES recipe(recipe_id)
);


INSERT INTO instruction (body, recipe) VALUES ("Sift together flour, salt, powdered milk, and backing powder in a large bowl.", 1);
INSERT INTO instruction (body, recipe) VALUES ("Pour water into mixture and stir with a fork until dough forms into a clump.", 1);
INSERT INTO instruction (body, recipe) VALUES ("Flour your hands.", 1);
INSERT INTO instruction (body, recipe) VALUES ("Mix the dough well with your hands, but do not knead the dough, forming a ball.", 1);
INSERT INTO instruction (body, recipe) VALUES ("Cut the ball into 4 peices.", 1);
INSERT INTO instruction (body, recipe) VALUES ("Form each section into a round disk 5-7 inches in diameter.", 1);
INSERT INTO instruction (body, recipe) VALUES ("Heat the vegetable oil (about 1 inch deep) to about 350 degrees.", 1);
INSERT INTO instruction (body, recipe) VALUES ("Fry each side until browned (3-4 minutes each side).", 1);
INSERT INTO instruction (body, recipe) VALUES ("Place fry bread on paper towel to absorb any excess oil.", 1);
INSERT INTO instruction (body, recipe) VALUES ("Brown ground meat and oinions in large frying pan on medium heat. You can also use the raw diced onions, instead of cooking them.", 2);
INSERT INTO instruction (body, recipe) VALUES ("Place fry bread cupped side up on a plates.", 2);
INSERT INTO instruction (body, recipe) VALUES ("Layer with remaining toppings.", 2);
INSERT INTO instruction (body, recipe) VALUES ("Dice the meat.", 3);
INSERT INTO instruction (body, recipe) VALUES ("Quarter the potatoes", 3);
INSERT INTO instruction (body, recipe) VALUES ("Dice onion.", 3);
INSERT INTO instruction (body, recipe) VALUES ("Heat mutton, in large pot with 3 1/2 cups of water, to boiling.", 3);
INSERT INTO instruction (body, recipe) VALUES ("Add remaining ingredients.", 3);
INSERT INTO instruction (body, recipe) VALUES ("Simmer for 2-3 hours. Can also cook in crock pot.", 3);
INSERT INTO instruction (body, recipe) VALUES ("Add salt to blood in large bowl.", 4);
INSERT INTO instruction (body, recipe) VALUES ("Mix in all ingredients.", 4);
INSERT INTO instruction (body, recipe) VALUES ("Stuff mixture into sheep stomachs or largest hog castings.", 4);
INSERT INTO instruction (body, recipe) VALUES ("Place sausages into boiling warer and poach at 80-85 degrees Celcius for about 60-90 minutes. Sausages should be between 68-70 degrees Celcius, stomach will require longer cooking time.", 4);
INSERT INTO instruction (body, recipe) VALUES ("Cool and keep in refridgerator.", 4);
INSERT INTO instruction (body, recipe) VALUES ("Bring water to a boil in a saucepan.", 5);
INSERT INTO instruction (body, recipe) VALUES ("Add juniper ashes and wisk in the cornmeal slowly to prevent lumping.", 5);
INSERT INTO instruction (body, recipe) VALUES ("Lower the heat and stir the cornmeal for 15 mintues, or intil it tastes done (smooth and firm)", 5);





CREATE TABLE history (
	history_id INTEGER PRIMARY KEY AUTOINCREMENT, 
	description BLOB,
	short_history TEXT,
	recipe INTEGER,
	FOREIGN KEY(recipe) REFERENCES recipe(recipe_id)
);



INSERT INTO history (description, short_history, recipe) VALUES ("The Navajo planters lived from the Earth as their ancestors had for hundreds of years before. They also raised livestock to feed their family. The Navajo dinetah (or homeland) was bordered by the four sacred mountains, from northeastern Arizona, western New Mexico, and north into Utah and Colorado. They planted crops in the fertile valley lands, such as Canyon de Chelly known for Ansazi ruins. The Navajo traded with the Spanish, Mexican, Pueblos, Apache, Comanche, and even the early American pioneers. Around 1846, large numbers of pioneers moved into the area and the cavalry came with them. This is when troubles began. The troubles escalated with the murder or Narbona (1766-1849), a well-respected Navajo leader on August 31, 1849. On this day, Narbona along with several hundred of his warriors, had come to meet and discuss peace with U.S. Colonel John M. Washington and others of the military stationed in the area. There had been trouble with the New Men (the New Mexican settlers who had driven Mexican settlers out of the area). After several hours, it was believed a settlement had been agreed upon. However, a young warrior by the name of Sadoval, had plans of his own. Mounting his horse he began to ride in front of the Navajo party, attempting to have them break the treaty. A U.S. Calvary soldier began to say that one of the horses ridden by a Navajo was his, and what peace there was in the meeting that was disintegrating into battle. Colonel Washington commanded the Navajo to stand down and return the horse to the soldier or he would fire into them. The rider and horse were now gone, and the Navajo party did not comply. A canon was fired, and Narbona was mortally wounded. It is told that he was scalped by a U.S. soldier as he lay dying. This disastrous attempt at peace led to the Long Walks. In September 1863, Kit Carson (1809-1868) was dispatched into Navajo land to retrieve a surrender. When no Navajo came to meet with him, he ordered the burning of the land. Attempts were made to starve out the Navajo and many were captured and taken to Bosque Redondo near Fort Sumner. Hundreds starved on the 300 mile walk and more would die later in the crowded and disparaging conditions. Navajo were placed with the Mescalero Apache where home peace was often not the case. The camps were meant for 4,000 to 5,000 people, yet there were now over 9,000 people, and supplies were meager. The government supplies of lard, flour, salt, sugar, baking powder or yeast, and powdered milk were often rancid. Fry bread came from these few foods provided during the 4 years of captivity. Since that time, it has become common food at most all PowWows of numerous tribes","To some, Indian Fry Bread is a sacred tradition. It is to be consumed by the people until the earth has again become purified. Wherever one finds Indian fry bread one finds its taco equivalent, and curiously enough, it’s often named after whichever tribe the reservation belongs to.",1);
INSERT INTO history (description, short_history, recipe) VALUES ("Indian fry bread is the foundation of a popular dish called Indian Tacos. Originally known as Navajo Tacos, they have been adopted by other tribes. The Navajo taco was voted the State Dish of Arizona in a 1995 poll conducted by the Arizona Republic newspaper. Indian tacos are the universal modern powwow food (see below). They are also popular attractions at many fairs, festivals, and outdoor summer shows held in the southwest. People will line up to wait their turn to buy some freshly made tacos. Indian tacos are a combination of beans or ground beef, chopped lettuce, sliced tomato, shredded Cheddar cheese, and optional green chile atop plate-sized rounds of crispy Navajo or Indian fry bread. No plates or silverware are need, as you just fill the fry bread with your desired filling, roll it up, and eat.","Indian fry bread is the foundation of a popular dish called Indian Tacos. Originally known as Navajo Tacos, they have been adopted by other tribes. ",2);
INSERT INTO history (description, short_history, recipe) VALUES ("Sheep are an important part of Navajo culture, and are raised for both meat and wool. Almost all of the parts of the sheep are eaten. Mutton stew is a traditional Navajo favorite.","Sheep are an important part of Navajo culture, and are raised for both meat and wool. Almost all of the parts of the sheep are eaten. Mutton stew is a traditional Navajo favorite.",3);
INSERT INTO history (description, short_history, recipe) VALUES ("Different cultures and/or regions have their own versions of blood sausage. These recipes are generally variable takes on a similar theme. Whatever the name – black pudding (UK, Ireland), boudin noir (France), blutwurst (Germany), morcilla (Spain), jelito (Czech), kaszanka (Poland), or mustamakkara (Finland), the main ingredients are as follows: blood – either from pig, sheep, lamb, cow, or goose (each author believing their choice is preferred); a filler that varies with region (e.g., oatmeal, buckwheat, breadcrumbs, barley, or other grains); onions and regional spices. All of these are typically smashed together and stuffed into to a sausage casing. The Navajo version, known also as dil, is “a blend of diced potatoes, celery, sheep fat, onion, cornmeal, salt and pepper mixed with fresh sheep blood.” What makes the Navajo one unique is that it is made from cornmeal.","What makes the Navajo one unique is that it is made from cornmeal.",4);
INSERT INTO history (description, short_history, recipe) VALUES ("Corn is one of the main staples of Native American life. It's an important food item, and every spring, many Navajo families plant large fields of corn. But its use goes far beyond just nutrition--it's also an important part of Navajo prayer. The pollen of the corn is dusted off the tassels and used in ceremonies as a blessing, and is offered in prayer. Corn is used to make many traditional dishes, including kneel-down bread, blue corn mush, dried steamed corn and roasted corn. The corn is also used during a ceremony when a Navajo girl comes of age--a large corn cake is cooked underground in a circular pit lined with corn husks.","Corn is one of the main staples of Native American life.",5);
