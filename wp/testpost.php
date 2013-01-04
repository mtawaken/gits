<?php
//this is  root/test/testpost.php
define( 'ABSPATH', dirname(__FILE__) . '/../' );
require_once( ABSPATH . 'wp-config.php' );
require_once( ABSPATH . 'wp-settings.php' );
require_once( ABSPATH . '/wp-includes/class-wp.php' );
require_once( ABSPATH . '/wp-includes/functions.php' );
require_once( ABSPATH . '/wp-includes/plugin.php' );

$wp = new WP();
$wp->main();

$my_post = array();
$my_post['post_title'] = 'My test';
$my_post['post_content'] = 'This is my post.';
$my_post['post_status'] = 'publish';
$my_post['post_author'] = 1;
$my_post['post_category'] = array(3);
$my_post['tags_input'] = array('tag1', 'tag2');
//$my_post['post_status'] = 'future';
//$my_post['post_date'] = '2010-07-04 16:20:03';

// Insert the post into the database
$ret = wp_insert_post( $my_post );
echo $ret;
?>
