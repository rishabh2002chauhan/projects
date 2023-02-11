function getRandomRolor() {
  var color = '#';
  for (var i = 0; i < 6; i++) {
    color += Math.floor(Math.random() * 10);
  }
  return color;
}
class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      quote: '',
      authorName: '' };

    this.handleSubmit = this.handleSubmit.bind(this);
  }
  handleSubmit() {

    fetch('https://api.quotable.io/random').
    then(response => response.json()).
    then(data => {
      this.setState({
        quote: data.content,
        authorName: data.author });

    });
    document.getElementById("quote-box").classList.add("show-example");
  }
  componentDidMount() {
    this.handleSubmit();
  }
  render() {
    const link = "https://twitter.com/intent/tweet?text=" + this.state.quote + "  -" + this.state.authorName;
    const color1 = getRandomRolor();
    const style1 = { backgroundColor: color1, height: '100vh', fontFamily: 'monospace' };
    const style2 = { color: color1, fontSize: '45px' };
    const style3 = { backgroundColor: 'white', opacity: '0.7' };
    return /*#__PURE__*/React.createElement("div", { id: "container1", className: "row align-items-center justify-content-center", style: style1 }, /*#__PURE__*/
    React.createElement("div", { id: "container2", className: "col-md-6 rounded ", style: style3 }, /*#__PURE__*/

    React.createElement("div", { id: "quote-box", className: " d-flex flex-column animate__animated animate__bounceInRight", style: style2, key: Math.random() }, /*#__PURE__*/
    React.createElement("div", { id: "text", className: "p-2", style: { fontWeight: 'bold' } },
    this.state.quote), /*#__PURE__*/

    React.createElement("div", { id: "author", className: "ms-auto p-2", style: { fontSize: '15px' } },
    this.state.authorName)), /*#__PURE__*/



    React.createElement("div", { id: "navbar", className: "d-flex mb-3" }, /*#__PURE__*/
    React.createElement("a", { className: "btn btn-outline-primary p-2", id: "tweet-quote", href: link, target: "_blank" }, /*#__PURE__*/React.createElement("i", { class: "fa-brands fa-twitter" })), /*#__PURE__*/
    React.createElement("button", { id: "new-quote", className: "ms-auto p-2 btn btn-outline-dark", onClick: this.handleSubmit }, "New Quote"))));




  }}

const ele = document.getElementById("container");
ReactDOM.render( /*#__PURE__*/React.createElement(App, null), ele);