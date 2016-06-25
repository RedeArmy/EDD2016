<?php
	$nombre = $_POST['Usuario'];
	$contra = $_POST['Contra'];
	$path1 = $_POST['Imagen1'];
	$path2 = $_POST['Imagen2'];
	
require_once __DIR__ . '/vendor/autoload.php';
use PhpAmqpLib\Connection\AMQPStreamConnection;
use PhpAmqpLib\Message\AMQPMessage;

class AgregarRpcClient {
	private $connection;
	private $channel;
	private $callback_queue;
	private $response;
	private $corr_id;
	
	public function __construct() {
		$this->connection = new AMQPStreamConnection('localhost', 5672, 'guest', 'guest');
		$this->channel = $this->connection->channel();
		list($this->callback_queue, ,) = $this->channel->queue_declare("", false, false, true, false);
		$this->channel->basic_consume($this->callback_queue, '', false, false, false, false, array($this, 'on_response'));
	}
	public function on_response($rep) {
		if($rep->get('correlation_id') == $this->corr_id) {	$this->response = $rep->body;}
	}
	public function call($n) {
		$this->response = null;
		$this->corr_id = uniqid();
		$msg = new AMQPMessage((string) $n, array('correlation_id' => $this->corr_id,'reply_to' => $this->callback_queue));
		$this->channel->basic_publish($msg, '', 'Proyecto1');
		while(!$this->response) {
			$this->channel->wait();
		}
		return intval($this->response);
	}
};
$agregar_rpc = new AgregarRpcClient();
$response = $agregar_rpc->call($nombre.",".$contra.",".$path1.",".$path2);
echo " [.] Got ", $response;
?>
