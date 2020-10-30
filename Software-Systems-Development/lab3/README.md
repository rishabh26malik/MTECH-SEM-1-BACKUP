# Lab activity 3

### CSS 
**1.)** `style.css` file contains the code of external CSS. 
Some thing different from what we discussed about CSS in lab which are used are :
`a,ul,p{`
  `font-family: "Arial";`
  `font-size: 18px;`
`}`
  - In the above code, multiple tags are together assigned some commom styling.

**2.)** `.center {`
  `display: block;`
  `margin-left: auto;`
  `margin-right: auto;`
  `max-width:100%;`
  `height:auto;`
`}`
  - In this code `center` is a class assigned to `img` tag in the html file. `class` is used to explicitly identify a particular tag used in an html file and not in general selecting all tags like one done in first css example explained above. 
  - **To center the image**, I have set left and right margin to `auto` so that it can adjust with different sizes of browers and made it into a `block` element. 
  - Also `max-width` is used so as to allow image to scale to different sizes of the browser.
**3.)** `#red {`
  `background-color: #f44336;`
  `border: 3px solid #000000;`
`}`
- In this `#red` is an `id` associated with a button to identify it particularly and apply specific css to it.
- `border` is used to give border to a button where `3px` is the width of border  line of button and `#000000` is the colour of border
- Similarly there are some other `ids` used like`green`, `reset` and `white` etc.

### HTML
- Unordered list tags `<ul>` are used at several places along with `<li>` tag
- `</br>` tag is used to insert new line
- `button` tag is used. 
- `onclick()` attribute is also used in `button` tag to call the javascript function associated to it in order to change the colour of a portion of web page 
### Javascript
 - `document.getElementById()` is used to update the background associate to a particular `id` which is mentioned in the function.
 - Javascript functions `ToRed`, `ToGreen`, `ToWhite` and `ToReset` are called when user clicks on the corresponding button