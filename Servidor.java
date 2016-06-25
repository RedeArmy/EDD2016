package Conexion;

import ListaSimple.Lista;
import ListaDoble.DLista;

import com.rabbitmq.client.AMQP;
import com.rabbitmq.client.Channel;
import com.rabbitmq.client.Connection;
import com.rabbitmq.client.ConnectionFactory;
import com.rabbitmq.client.Consumer;
import com.rabbitmq.client.ConsumerCancelledException;
import com.rabbitmq.client.DefaultConsumer;
import com.rabbitmq.client.Envelope;
import com.rabbitmq.client.QueueingConsumer;
import com.rabbitmq.client.ShutdownSignalException;
import java.io.IOException;
import java.util.concurrent.TimeoutException;

public class RecibirAdmin {

    private static final String RPC_QUEUE_NAME = "Proyecto1";
    
    public DLista listadoble = new DLista();
    public Lista lista = new Lista();

    public void RecibirUser() {
        Connection connection = null;
        Channel channel = null;
        try {
            ConnectionFactory factory = new ConnectionFactory();
            factory.setHost("localhost");

            connection = factory.newConnection();
            channel = connection.createChannel();

            channel.queueDeclare(RPC_QUEUE_NAME, false, false, false, null);

            channel.basicQos(1);

            QueueingConsumer consumer = new QueueingConsumer(channel);
            channel.basicConsume(RPC_QUEUE_NAME, false, consumer);

            System.out.println(" [x] Awaiting RPC requests");

            while (true) {
                String response = null;

                QueueingConsumer.Delivery delivery = consumer.nextDelivery();

                AMQP.BasicProperties props = delivery.getProperties();
                AMQP.BasicProperties replyProps = new AMQP.BasicProperties.Builder()
                        .correlationId(props.getCorrelationId())
                        .build();

                try {
                    String message = new String(delivery.getBody(), "UTF-8");

                    System.out.println(" [x] Received '" + message);
                    response = "" + Agregar(message);
                } catch (Exception e) {
                    System.out.println(" [.] " + e.toString());
                    response = "";
                } finally {
                    channel.basicPublish("", props.getReplyTo(), replyProps, response.getBytes("UTF-8"));
                    channel.basicAck(delivery.getEnvelope().getDeliveryTag(), false);
                }
            }
        } catch (IOException | TimeoutException | InterruptedException | ShutdownSignalException | ConsumerCancelledException e) {
            e.printStackTrace();
        } finally {
            if (connection != null) {
                try {
                    connection.close();
                } catch (Exception ignore) {
                }
            }
        }

    }

    public void Actualizar(String dato) {
        String[] cadena = dato.split(",");
        listadoble.update(cadena[0], cadena[1], cadena[2]);
    }

    public String Agregar(String dato) {
       String[] cadena = dato.split(",");
        System.out.println(cadena[0]);
        System.out.println(cadena[1]);
       // System.out.println(cadena[2]);
        //if(cadena[3]!=null){
        //System.out.println(cadena[3]);}
        //listadoble.add(cadena[0], cadena[1], "usuario");
        //listadoble.get(cadena[0]).addImagen(cadena[2], cadena[3]);
        return cadena[0];
    }
    
    public void AgregarImage(String dato) {
        String[] cadena = dato.split(",");
        listadoble.add(cadena[0], cadena[1], cadena[3]);
        listadoble.get(cadena[0]).addImagen(cadena[3], "");
        
    }
    
    public void LlenarListaD(String dato) {
        String[] cadena = dato.split(",");

        if (cadena[2] == "" && cadena[3] == "") {
            listadoble.add(cadena[0], cadena[1], "usuario");
        } else if (cadena[2] == "") {
            listadoble.add(cadena[0], cadena[1], "usuario");
            listadoble.get(cadena[0]).addImagen(cadena[3], "");
        } else if (cadena[3] == "") {
            listadoble.add(cadena[0], cadena[1], "usuario");
            listadoble.get(cadena[0]).addImagen(cadena[2], "");
        } else {
            listadoble.add(cadena[0], cadena[1], "usuario");
            listadoble.get(cadena[0]).addImagen(cadena[2], cadena[3]);
        }
    }
    
    public void Eliminar(String dato){
        listadoble.delete(dato);
    }
  
    
}
